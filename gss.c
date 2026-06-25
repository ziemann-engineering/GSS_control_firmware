/*
 * gss.c - GSS Control Software
 * STM32G474RE, ChibiOS 21.11
 *
 * Gate Stress Switching (GSS) test implementation.
 *
 * HRTIM usage:
 *   Master timer: free-running reference, no outputs.
 *   Timers C, D, E, F: one output pair each, all synchronised to master period.
 *   All 8 outputs switch at the same frequency and duty cycle.
 *
 * Batch flow:
 *   1. cmd_GSS_test() copies parameters, signals GSS_start_sem, then blocks
 *      on GSS_done_sem — the shell command does not return until the batch
 *      is complete.  This means only one command is active at a time.
 *   2. Background test thread sleeps for (cycles / freq) seconds, then stops
 *      HRTIM and signals GSS_done_sem.
 *   3. cmd_GSS_test wakes, prints "TEST_COMPLETE <total>" and returns to
 *      the shell, which then accepts the next command.
 *   4. Python GUI can now call measure_DUT / measure_supply / Vth as needed,
 *      then send the next GSS_test batch.
 *
 * Note: the shell is blocked during a batch.  To abort, reset the MCU.
 */

#include "main.h"
#include "gss.h"

/* -------------------------------------------------------------------------
 * Module state
 * -------------------------------------------------------------------------*/

volatile bool           GSS_test_running_flag = false;
thread_reference_t      GSS_test_thread_p     = NULL;
volatile uint64_t       GSS_cycle_count       = 0;

/* Static test parameters — written by cmd_GSS_test, read by test thread */
static GSS_test_params_t GSS_pending_params;

/* GSS_start_sem: cmd_GSS_test signals this to start the batch */
static semaphore_t GSS_start_sem;
/* GSS_done_sem:  test thread signals this when the batch finishes */
static semaphore_t GSS_done_sem;

/* -------------------------------------------------------------------------
 * HRTIM helpers
 * -------------------------------------------------------------------------*/

/*
 * GSS_hrtim_configure() - set up HRTIM1 timers A-D for synchronised switching.
 *
 * Selects the lowest CKPSC (prescaler) value that keeps the 16-bit period
 * register in range [3, 65535].  All slave timers copy the same period and
 * compare value from the master.
 *
 * TBD: palSetPadMode() calls below must be updated with the actual HRTIM
 *      output pin assignments once the PCB layout is finalised.
 *      AF13 is used for HRTIM outputs on STM32G474.
 */
static void GSS_hrtim_configure(float freq_hz, float duty) {
    uint32_t ckpsc, period, cmp1;
    /* Use uint64_t: GSS_HRTIM_CLOCK is 4 GHz which fits uint32_t but
     * intermediate products can overflow 32 bits at low frequencies. */
    uint64_t f_hrtim = (uint64_t)GSS_HRTIM_CLOCK;

    /* Find smallest prescaler that fits period in 16-bit register */
    ckpsc = 0;
    do {
        uint64_t p64 = f_hrtim / ((1ULL << ckpsc) * (uint64_t)(uint32_t)freq_hz);
        if (p64 >= 3 && p64 <= 65535U) {
            period = (uint32_t)p64;
            break;
        }
        ckpsc++;
    } while (ckpsc <= 7);

    if (ckpsc > 7) {
        ckpsc   = 7;
        period  = 65535U;
    }

    cmp1 = (uint32_t)((float)period * duty + 0.5f);
    if (cmp1 >= period) cmp1 = period - 1;
    if (cmp1 < 1)       cmp1 = 1;

    /* Enable HRTIM clock */
    RCC->APB2ENR |= RCC_APB2ENR_HRTIM1EN;
    __DSB();

    /* DLL calibration — must run before configuring timers.
     * Enables 4 GHz high-resolution clock (125 MHz APB2 timer × 32). */
    HRTIM1->sCommonRegs.DLLCR = HRTIM_DLLCR_CALRTE_1 | HRTIM_DLLCR_CAL;
    while (!(HRTIM1->sCommonRegs.ISR & HRTIM_ISR_DLLRDY)) {}  /* ~10 μs */

    /* -----------------------------------------------------------------------
     * Configure HRTIM output GPIO pins as AF13.
     * Board.h already sets these at startup; palSetPadMode calls are redundant
     * but kept here for clarity. Remove if startup config is confirmed correct.
     * Timers C,D → GPIOB; Timers E,F → GPIOC.
     * ----------------------------------------------------------------------- */
    palSetPadMode(GPIOB, 12U, PAL_MODE_ALTERNATE(13)); /* PB12 CHC1 */
    palSetPadMode(GPIOB, 13U, PAL_MODE_ALTERNATE(13)); /* PB13 CHC2 */
    palSetPadMode(GPIOB, 14U, PAL_MODE_ALTERNATE(13)); /* PB14 CHD1 */
    palSetPadMode(GPIOB, 15U, PAL_MODE_ALTERNATE(13)); /* PB15 CHD2 */
    palSetPadMode(GPIOC, 8U,  PAL_MODE_ALTERNATE(3));  /* PC8  CHE1 (AF3) */
    palSetPadMode(GPIOC, 9U,  PAL_MODE_ALTERNATE(3));  /* PC9  CHE2 (AF3) */
    palSetPadMode(GPIOC, 6U,  PAL_MODE_ALTERNATE(13)); /* PC6  CHF1 */
    palSetPadMode(GPIOC, 7U,  PAL_MODE_ALTERNATE(13)); /* PC7  CHF2 */

    /* ----- Master timer: enable slave timers C, D, E, F ----- */
    HRTIM1->sMasterRegs.MPER = period;
    HRTIM1->sMasterRegs.MCR  = ((ckpsc << HRTIM_MCR_CK_PSC_Pos) |
                                 HRTIM_MCR_CONT    |   /* continuous mode */
                                 HRTIM_MCR_PREEN   |   /* preload enable  */
                                 HRTIM_MCR_TCCEN   |   /* enable timer C  */
                                 HRTIM_MCR_TDCEN   |   /* enable timer D  */
                                 HRTIM_MCR_TECEN   |   /* enable timer E  */
                                 HRTIM_MCR_TFCEN   |   /* enable timer F  */
                                 HRTIM_MCR_MCEN);      /* enable master   */

    /* ----- Slave timers C(2), D(3), E(4), F(5): identical configuration ----- */
    uint32_t timcr = ((ckpsc << HRTIM_TIMCR_CK_PSC_Pos) |
                      HRTIM_TIMCR_CONT   |
                      HRTIM_TIMCR_PREEN);

    for (int i = 2; i <= 5; i++) {
        HRTIM1->sTimerxRegs[i].TIMxCR  = timcr;
        HRTIM1->sTimerxRegs[i].PERxR   = period;
        HRTIM1->sTimerxRegs[i].CMP1xR  = cmp1;
        /* Reset slave counter on master period event (keeps all timers in sync) */
        HRTIM1->sTimerxRegs[i].RSTxR   = HRTIM_RSTR_MSTPER;
        /* Output 1: set on timer period event, reset on CMP1 */
        HRTIM1->sTimerxRegs[i].SETx1R  = HRTIM_SET1R_PER;
        HRTIM1->sTimerxRegs[i].RSTx1R  = HRTIM_RST1R_CMP1;
        /* Output 2: same timing as output 1 (same bit positions in SETx2R/RSTx2R) */
        HRTIM1->sTimerxRegs[i].SETx2R  = HRTIM_SET1R_PER;   /* PER bit is same pos */
        HRTIM1->sTimerxRegs[i].RSTx2R  = HRTIM_RST1R_CMP1;  /* CMP1 bit is same pos */
    }

    /* Enable outputs: CHC1/2 (PB12/13), CHD1/2 (PB14/15), CHE1/2 (PC8/9), CHF1/2 (PC6/7) */
    HRTIM1->sCommonRegs.OENR = (HRTIM_OENR_TC1OEN | HRTIM_OENR_TC2OEN |
                                 HRTIM_OENR_TD1OEN | HRTIM_OENR_TD2OEN |
                                 HRTIM_OENR_TE1OEN | HRTIM_OENR_TE2OEN |
                                 HRTIM_OENR_TF1OEN | HRTIM_OENR_TF2OEN);
}

/*
 * GSS_hrtim_stop() - disable outputs and stop counters.
 */
static void GSS_hrtim_stop(void) {
    HRTIM1->sCommonRegs.ODISR = (HRTIM_ODISR_TC1ODIS | HRTIM_ODISR_TC2ODIS |
                                  HRTIM_ODISR_TD1ODIS | HRTIM_ODISR_TD2ODIS |
                                  HRTIM_ODISR_TE1ODIS | HRTIM_ODISR_TE2ODIS |
                                  HRTIM_ODISR_TF1ODIS | HRTIM_ODISR_TF2ODIS);
    HRTIM1->sMasterRegs.MCR &= ~(HRTIM_MCR_MCEN  |
                                  HRTIM_MCR_TCCEN | HRTIM_MCR_TDCEN |
                                  HRTIM_MCR_TECEN | HRTIM_MCR_TFCEN);
}

/* -------------------------------------------------------------------------
 * ADC supply measurement
 * -------------------------------------------------------------------------*/

/*
 * GSS_adc_read_channel() - perform a single software-triggered ADC conversion.
 * Uses ADC1 directly (no ChibiOS ADC driver).
 *
 * TBD: ADC1 must be powered and calibrated in GSS_init().
 *      This function assumes the ADC is already enabled and calibrated.
 */
static uint16_t GSS_adc_read_channel(uint32_t channel) {
    /* Set sequence length = 1, channel = channel */
    ADC5->SQR1 = (channel << ADC_SQR1_SQ1_Pos);

    /* Start conversion */
    ADC5->CR |= ADC_CR_ADSTART;

    /* Wait for end of conversion */
    uint32_t timeout = 1000000UL;
    while (!(ADC5->ISR & ADC_ISR_EOC) && timeout--);

    uint16_t result = (uint16_t)(ADC5->DR & 0x0FFFU);
    ADC5->ISR = ADC_ISR_EOC;   /* clear flag */
    return result;
}

/*
 * GSS_adc_init() - enable and calibrate ADC5 for supply measurement.
 * Called once from GSS_init().
 */
static void GSS_adc_init(void) {
    /* Enable ADC345 peripheral clock (on AHB2) */
    RCC->AHB2ENR |= RCC_AHB2ENR_ADC345EN;
    __DSB();

    /* Exit deep power down mode */
    ADC5->CR &= ~ADC_CR_DEEPPWD;
    /* Enable internal voltage regulator */
    ADC5->CR |= ADC_CR_ADVREGEN;
    /* Wait for regulator startup (~20 µs) */
    for (volatile uint32_t i = 0; i < 5000; i++);

    /* Calibrate (single-ended) */
    ADC5->CR &= ~ADC_CR_ADCALDIF;
    ADC5->CR |= ADC_CR_ADCAL;
    while (ADC5->CR & ADC_CR_ADCAL);

    /* Configure clock: synchronous, HCLK/4 */
    ADC345_COMMON->CCR = ADC_CCR_CKMODE_1;  /* CKMODE = 10b = HCLK/4 */

    /* Enable ADC */
    ADC5->ISR = ADC_ISR_ADRDY;
    ADC5->CR |= ADC_CR_ADEN;
    while (!(ADC5->ISR & ADC_ISR_ADRDY));

    /* Set sampling time for channels 1 and 2: 92.5 cycles */
    ADC5->SMPR1 = (ADC_SMPR1_SMP1_2 | ADC_SMPR1_SMP1_1 | ADC_SMPR1_SMP1_0 |
                   ADC_SMPR1_SMP2_2 | ADC_SMPR1_SMP2_1 | ADC_SMPR1_SMP2_0);
}

/* -------------------------------------------------------------------------
 * Test thread
 * -------------------------------------------------------------------------*/

static THD_WORKING_AREA(waGSStest, 1024);
static THD_FUNCTION(GSS_test_thread, arg) {
    (void)arg;
    chRegSetThreadName("GSS_test");

    while (true) {
        /* Wait for cmd_GSS_test to post a batch */
        chSemWait(&GSS_start_sem);

        GSS_test_params_t p = GSS_pending_params;   /* copy by value */

        float    freq_hz = p.frequency_hz;
        float    duty    = p.duty_cycle;
        uint32_t cycles  = p.cycles;

        /* Duration in ms, rounded up to at least 1 ms */
        uint32_t duration_ms = (uint32_t)((float)cycles / freq_hz * 1000.0f + 0.5f);
        if (duration_ms < 1) duration_ms = 1;

        GSS_test_running_flag = true;
        GSS_cycle_count      += cycles;   /* accumulate across batches */

        /* Enable gate driver: pull GD_DIS low (open-drain, hardware pullup released) */
        palClearLine(LINE_GD_DIS);
        chThdSleepMicroseconds(10);  /* allow gate driver to settle before switching */

        /* Configure and start HRTIM */
        GSS_hrtim_configure(freq_hz, duty);

        /* Sleep for batch duration.
         * chThdSuspendTimeoutS allows stop_test() to interrupt via MSG_RESET
         * if a stop path is ever added (e.g. hardware button). */
        chSysLock();
        chThdSuspendTimeoutS(&GSS_test_thread_p, TIME_MS2I(duration_ms));
        chSysUnlock();

        GSS_hrtim_stop();
        /* Disable gate driver: release open-drain, hardware pullup drives GD_DIS high */
        palSetLine(LINE_GD_DIS);
        GSS_test_running_flag = false;

        /* Wake cmd_GSS_test so it can return to the shell */
        chSemSignal(&GSS_done_sem);
    }
}

/* -------------------------------------------------------------------------
 * Shell commands
 * -------------------------------------------------------------------------*/

/*
 * GSS_test <cycles> <freq_hz> <duty_0_to_1>
 *
 * Runs one batch of <cycles> switching cycles at <freq_hz> Hz with <duty>
 * duty cycle.  The command blocks until the batch completes, then prints
 * "TEST_COMPLETE <total_accumulated_cycles>" and returns to the shell.
 *
 * Python calls this once per batch.  Between batches the shell is free for
 * measure_DUT, measure_supply, etc.
 */
void cmd_GSS_test(BaseSequentialStream *chp, int argc, char *argv[]) {
    led_cmd_flag = true;
    if (argc != 3) {
        chprintf(chp, "Usage: GSS_test <cycles> <freq_hz> <duty>\r\n");
        return;
    }

    if (GSS_test_running_flag) {
        chprintf(chp, "ERROR: test already running\r\n");
        return;
    }

    uint32_t cycles = (uint32_t)strtoul(argv[0], NULL, 10);
    float    freq   = strtof(argv[1], NULL);
    float    duty   = strtof(argv[2], NULL);

    if (cycles == 0 || freq <= 0.0f || duty <= 0.0f || duty >= 1.0f) {
        chprintf(chp, "ERROR: invalid parameters\r\n");
        return;
    }

    GSS_pending_params.cycles       = cycles;
    GSS_pending_params.frequency_hz = freq;
    GSS_pending_params.duty_cycle   = duty;

    /* Wake the test thread and block until it finishes the batch */
    chSemSignal(&GSS_start_sem);
    chSemWait(&GSS_done_sem);

    chprintf(chp, "TEST_COMPLETE %lu\r\n", (unsigned long)GSS_cycle_count);
}

/*
 * GSS_cycles - report total accumulated cycle count across all batches.
 */
void cmd_GSS_cycles(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argc; (void)argv;
    led_cmd_flag = true;
    chprintf(chp, "CYCLES %lu\r\n", (unsigned long)GSS_cycle_count);
}

/*
 * measure_supply - read positive and negative gate supply voltages via ADC5.
 *
 * Positive rail:  V_pos = (raw / 4096) * 3.3 * 11  (resistor divider to GND)
 * Negative rail:  V_neg = 3.3 - 11 * raw / 4096
 *   The negative rail is biased to VREF at the ADC pin when supply = 0,
 *   so the result is referenced to 3.3 V and scaled by the divider ratio.
 */
void cmd_measure_supply(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argc; (void)argv;
    led_cmd_flag = true;

    uint16_t raw_pos = GSS_adc_read_channel(ADC_CH_VPOS);
    uint16_t raw_neg = GSS_adc_read_channel(ADC_CH_VNEG);

    float v_pos = ((float)raw_pos / (float)ADC_RESOLUTION) * ADC_VREF * ADC_VPOS_DIVIDER;
    float v_neg = ADC_VREF - ADC_VNEG_DIVIDER * (float)raw_neg / (float)ADC_RESOLUTION;

    /* Protocol: "POS:+xx.xx NEG:-yy.yy" */
    chprintf(chp, "POS:+%.2f NEG:%.2f\r\n", (double)v_pos, (double)v_neg);
}

/*
 * measure_DUT <n> - connect DUT n (1-8) to SMU contacts, or 0 to deselect all.
 *
 * TBD: GSS_DUT_SEL_PORT and GSS_DUT_SEL_MASK must be set in gss.h when the
 *      PCB pin assignment is finalised.  The 8 DUT select lines are driven as
 *      a one-hot pattern on consecutive port bits defined by GSS_DUT_SEL_MASK.
 */
void cmd_measure_DUT(BaseSequentialStream *chp, int argc, char *argv[]) {
    led_cmd_flag = true;
    if (argc != 1) {
        chprintf(chp, "Usage: measure_DUT <0-8>\r\n");
        return;
    }

    uint32_t dut = (uint32_t)strtoul(argv[0], NULL, 10);
    if (dut > GSS_NUM_DUTS) {
        chprintf(chp, "ERROR: DUT index out of range\r\n");
        return;
    }

    /* Build one-hot pattern on the LSBs; GSS_DUT_SEL_MASK defines which bits */
    uint32_t pattern = 0;
    if (dut > 0) {
        pattern = (1UL << (dut - 1U)) & GSS_DUT_SEL_MASK;
    }

    /* Write relay pattern atomically: clear all relay bits then set selected bit */
    palWriteGroup(GSS_DUT_SEL_PORT, GSS_DUT_SEL_MASK, 0U, pattern);

    chprintf(chp, "OK\r\n");
}

/*
 * ID - read the 8 board identification pins and return hex serial number.
 *
 * Response format:
 *   "Ziemann Engineering,GSS Control Board,XX,0.1 / <build date>\r\n"
 *
 * TBD: GSS_ID_PORT and GSS_ID_MASK must be set in gss.h when the PCB pin
 *      assignment is finalised.  The 8 ID lines are expected on consecutive
 *      bits defined by GSS_ID_MASK (LSB-aligned).
 */
void cmd_ID(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argc; (void)argv;
    led_cmd_flag = true;

    /* Read the port and extract the 8 ID bits */
    uint32_t port_val = GSS_ID_PORT->IDR;
    /* Find first set bit in mask to determine bit offset */
    uint32_t shift = 0;
    uint32_t mask  = GSS_ID_MASK;
    while (mask && !(mask & 1U)) {
        mask >>= 1;
        shift++;
    }
    uint8_t sn = (uint8_t)((port_val >> shift) & 0xFFU);

    chprintf(chp, "Ziemann Engineering,GSS Control Board,%02X,%s / %s\r\n",
             sn, GSS_FW_VERSION_STR, GSS_FW_BUILD_DATE);
}

/* -------------------------------------------------------------------------
 * Module initialisation
 * -------------------------------------------------------------------------*/

void GSS_init(void) {
    /* Resume semaphore and start/done semaphores */
    chSemObjectInit(&GSS_start_sem, 0);
    chSemObjectInit(&GSS_done_sem,  0);
    GSS_cycle_count = 0;

    /* ADC5 for supply measurement */
    GSS_adc_init();

    /* DUT select pins: PA0-PA7 (RLC1-RLC8) — relay coil drive outputs */
    palSetGroupMode(GSS_DUT_SEL_PORT, GSS_DUT_SEL_MASK, 0U,
                    PAL_MODE_OUTPUT_PUSHPULL);
    palWriteGroup(GSS_DUT_SEL_PORT, GSS_DUT_SEL_MASK, 0U, 0U); /* all off */

    /* ID input pins: PB0-PB7 — pull-down, read serial number */
    palSetGroupMode(GSS_ID_PORT, GSS_ID_MASK, 0U,
                    PAL_MODE_INPUT_PULLDOWN);

    /* GD_DIS (PB11): open-drain output, high at startup — gate driver disabled.
     * Board.h sets ODR=HIGH; reinforce here before any switching is possible. */
    palSetLineMode(LINE_GD_DIS, PAL_MODE_OUTPUT_OPENDRAIN);
    palSetLine(LINE_GD_DIS);

    /* Start the background test thread (blocks on mailbox until a test starts) */
    chThdCreateStatic(waGSStest, sizeof(waGSStest), NORMALPRIO,
                      GSS_test_thread, NULL);
}
