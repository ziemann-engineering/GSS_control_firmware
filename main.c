/*
 * main.c - GSS Control Software
 * STM32G474RE, ChibiOS 21.11
 *
 * Commands via USB CDC shell:
 *   GSS_test  <cycles> <freq_hz> <duty>  - run one batch; blocks until done
 *   GSS_cycles                           - query total cycle count so far
 *   measure_supply                       - read gate supply voltages
 *   measure_DUT  <0-8>                   - select DUT (0=none)
 *   ID / *IDN?                           - returns \"Ziemann Engineering,GSS Control Board,SN,version / date\"
 *   status                               - print running state
 *   stop                                 - abort test (between batches only)
 *   dfu                                  - reboot into USB DFU bootloader
 *   reset                                - software reset
 */

#include "main.h"
#include "gss.h"

// ########################
// ##  Global Variables  ##
// ########################

BaseSequentialStream *chp_USB = (BaseSequentialStream *)&SDU1;

volatile bool clear_to_run_flag = false;
volatile bool GSS_error_flag   = false;
volatile bool led_cmd_flag     = false;

// ############################
// ## Built-in shell commands ##
// ############################

static void cmd_status(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argc; (void)argv;
    led_cmd_flag = true;
    if (GSS_test_running_flag)
        chprintf(chp, "Test running: GSS\r\n");
    else
        chprintf(chp, "None\r\n");
}

static void cmd_stop(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argc; (void)argv;
    led_cmd_flag = true;
    stop_test();
    chprintf(chp, "OK\r\n");
}

static void cmd_dfu(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argc; (void)argv;
    led_cmd_flag = true;
    chprintf(chp, "Entering DFU bootloader...\r\n");
    chThdSleepMilliseconds(100);   /* allow USB to flush response */

    /* Drive PB8 high; capacitor charges BOOT0 so ROM bootloader starts
     * after the reset below. */
    palSetPadMode(GPIOB, GPIOB_BOOT0_CTRL, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(GPIOB, GPIOB_BOOT0_CTRL);
    chThdSleepMilliseconds(200);   /* wait for capacitor to charge */

    NVIC_SystemReset();
}

static void cmd_reset(BaseSequentialStream *chp, int argc, char *argv[]) {
    (void)argc; (void)argv;
    led_cmd_flag = true;
    chprintf(chp, "Resetting...\r\n");
    chThdSleepMilliseconds(50);
    NVIC_SystemReset();
}

// ####################################
// ##  Shell command table           ##
// ####################################

static const ShellCommand commands[] = {
    {"GSS_test",       cmd_GSS_test},
    {"GSS_cycles",     cmd_GSS_cycles},
    {"measure_supply", cmd_measure_supply},
    {"measure_DUT",    cmd_measure_DUT},
    {"ID",             cmd_ID},
    {"*IDN?",          cmd_ID},
    {"status",         cmd_status},
    {"stop",           cmd_stop},
    {"dfu",            cmd_dfu},
    {"reset",          cmd_reset},
    {NULL, NULL}
};

static const ShellConfig shell_cfg1 = {
    (BaseSequentialStream *)&SDU1,
    commands
};

// ####################################
// ##  stop_test()                   ##
// ####################################

void stop_test(void) {
    /* Disable HRTIM outputs: CHC1/2, CHD1/2, CHE1/2, CHF1/2 */
    HRTIM1->sCommonRegs.ODISR = (HRTIM_ODISR_TC1ODIS | HRTIM_ODISR_TC2ODIS |
                                  HRTIM_ODISR_TD1ODIS | HRTIM_ODISR_TD2ODIS |
                                  HRTIM_ODISR_TE1ODIS | HRTIM_ODISR_TE2ODIS |
                                  HRTIM_ODISR_TF1ODIS | HRTIM_ODISR_TF2ODIS);
    /* Stop master and slave counters C, D, E, F */
    HRTIM1->sMasterRegs.MCR &= ~(HRTIM_MCR_MCEN  |
                                  HRTIM_MCR_TCCEN | HRTIM_MCR_TDCEN |
                                  HRTIM_MCR_TECEN | HRTIM_MCR_TFCEN);

    GSS_test_running_flag = false;

    /* Release GD_DIS: open-drain released, hardware pullup disables gate driver */
    palSetLine(LINE_GD_DIS);

    /* Wake up any waiting test thread so it can exit cleanly */
    chSysLock();
    if (GSS_test_thread_p != NULL) {
        chThdResumeI(&GSS_test_thread_p, MSG_RESET);
    }
    chSysUnlock();
}

// ####################################
// ##  LED blink thread              ##
// ####################################

static THD_WORKING_AREA(waLED, 256);
static THD_FUNCTION(LED_thread, arg) {
    (void)arg;
    chRegSetThreadName("LED");

    systime_t next_heartbeat = chVTGetSystemTime();

    while (true) {
        chThdSleepMilliseconds(50);

        /* Red/Green: reflect GD state (mutually exclusive, steady) */
        if (GSS_test_running_flag) {
            palSetPad(GPIOC, GPIOC_LED_RED);
            palClearPad(GPIOC, GPIOC_LED_GREEN);
        } else {
            palClearPad(GPIOC, GPIOC_LED_RED);
            palSetPad(GPIOC, GPIOC_LED_GREEN);
        }

        /* Yellow: error indicator — latched until reset */
        if (GSS_error_flag) {
            palSetPad(GPIOC, GPIOC_LED_YELLOW);
        }

        /* Blue: 50 ms pulse every second (heartbeat), also fires on any command */
        if (led_cmd_flag ||
            chVTTimeElapsedSinceX(next_heartbeat) >= TIME_MS2I(1000)) {
            palSetPad(GPIOC, GPIOC_LED_BLUE);
            chThdSleepMilliseconds(led_cmd_flag ? 500 : 50);
            palClearPad(GPIOC, GPIOC_LED_BLUE);
            led_cmd_flag   = false;
            next_heartbeat = chVTGetSystemTime();
        }
    }
}

// ####################################
// ##  main()                        ##
// ####################################

int main(void) {
    halInit();
    chSysInit();

    /* USB CDC serial driver init */
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    /* Activate USB driver; board will appear to host after a short delay */
    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1500);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);

    /* Shell subsystem */
    shellInit();

    /* Startup LED test: all four LEDs on for 300 ms */
    palSetPad(GPIOC, GPIOC_LED_RED);
    palSetPad(GPIOC, GPIOC_LED_GREEN);
    palSetPad(GPIOC, GPIOC_LED_BLUE);
    palSetPad(GPIOC, GPIOC_LED_YELLOW);
    chThdSleepMilliseconds(300);
    palClearPad(GPIOC, GPIOC_LED_RED);
    palClearPad(GPIOC, GPIOC_LED_GREEN);
    palClearPad(GPIOC, GPIOC_LED_BLUE);
    palClearPad(GPIOC, GPIOC_LED_YELLOW);

    /* Start LED thread */
    chThdCreateStatic(waLED, sizeof(waLED), LOWPRIO, LED_thread, NULL);

    /* Initialise GSS module (semaphore, mailbox, test thread) */
    GSS_init();

    clear_to_run_flag = true;

    /* Shell loop: restart shell if it exits (e.g. USB disconnect/reconnect) */
    static THD_WORKING_AREA(waShell, 2048);
    thread_t *shelltp = NULL;
    while (true) {
        if (shelltp == NULL || chThdTerminatedX(shelltp)) {
            /* Wait for USB to be ready */
            if (SDU1.state == SDU_READY) {
                shelltp = chThdCreateStatic(waShell, sizeof(waShell),
                                            NORMALPRIO + 1,
                                            shellThread,
                                            (void *)&shell_cfg1);
            }
        }
        chThdSleepMilliseconds(200);
    }
}
