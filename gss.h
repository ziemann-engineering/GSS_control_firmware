/*
 * gss.h - GSS Control Software
 * STM32G474RE, ChibiOS 21.11
 *
 * Gate Stress Switching test module.
 *
 * HRTIM1 slave timers C, D, E, F used (8 outputs total):
 *   CHC1=PB12, CHC2=PB13  (PWM1/PWM2)
 *   CHD1=PB14, CHD2=PB15  (PWM3/PWM4)
 *   CHE1=PC8,  CHE2=PC9   (PWM5/PWM6)
 *   CHF1=PC6,  CHF2=PC7   (PWM7/PWM8)
 *   All outputs configured as AF13 in board.h.
 *
 * Clock: 20 MHz HSE crystal → PLL → 125 MHz sysclock.
 * HRTIM input clock = 2 × fAPB2 = 250 MHz (APB2 prescaler = 1).
 *
 * ADC supply measurement:
 *   Uses ADC5, channel 1 (AIN1) and channel 2 (AIN2).
 *
 * DUT selection: PA0-PA7 (RLC1-RLC8) — relay control outputs.
 * ID input:      PB0-PB7 — board serial number (pull-down inputs).
 */

#ifndef GSS_H_
#define GSS_H_

#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

/* -------------------------------------------------------------------------
 * Hardware constants (update when PCB pin assignment is finalised)
 * -------------------------------------------------------------------------*/

#define GSS_FW_VERSION_STR      "0.1"   /* increment on every firmware release */
#define GSS_FW_BUILD_DATE        __DATE__

/* HRTIM clock: HSE 20 MHz → PLL → 125 MHz SYSCLK.
 * APB2 prescaler = /2 → PCLK2 = 62.5 MHz → APB2 timer clock = 125 MHz.
 * HRTIM1 DLL enabled: 125 MHz × 32 = 4 GHz high-resolution clock.
 * Period/compare register calculations use this 4 GHz base. */
#define GSS_HRTIM_CLOCK         4000000000UL  /* Hz (DLL × 32 output) */

/* ADC supply voltage conversion.
 * ADC reference = 3.3 V, 12-bit resolution.
 * Positive supply: measured via resistor divider (R1+R2)/R2 = 11 */
#define ADC_VPOS_DIVIDER        11.0f   /* (R1+R2)/R2 for +supply divider */
#define ADC_VNEG_DIVIDER        11.0f   /* (R1+R2)/R2 for -supply divider */
#define ADC_VREF                3.3f
#define ADC_RESOLUTION          4096U

/* ADC5, channels 1 and 2 for supply measurement. */
#define ADC_CH_VPOS             1U      /* ADC5 channel 1 = AIN1 (positive supply) */
#define ADC_CH_VNEG             2U      /* ADC5 channel 2 = AIN2 (negative supply) */

/* DUT select: PA0-PA7 (RLC1-RLC8) drive relay coils to connect DUT to SMU. */
#define GSS_DUT_SEL_PORT        GPIOA
#define GSS_DUT_SEL_MASK        0x00FFU  /* PA0..PA7 */

/* ID input: PB0-PB7 read the 8-bit board serial number (pull-down inputs). */
#define GSS_ID_PORT             GPIOB
#define GSS_ID_MASK             0x00FFU  /* PB0..PB7 */

/* Number of DUT positions and ID bits */
#define GSS_NUM_DUTS            8U
#define GSS_NUM_ID_BITS         8U

/* -------------------------------------------------------------------------
 * Test parameter structure
 * -------------------------------------------------------------------------*/

typedef struct {
    uint32_t    cycles;           /* total switching cycles in this batch    */
    float       frequency_hz;     /* switching frequency (Hz)                */
    float       duty_cycle;       /* duty cycle 0.0 - 1.0                    */
} GSS_test_params_t;

/* -------------------------------------------------------------------------
 * Shared state (defined in gss.c)
 * -------------------------------------------------------------------------*/

extern volatile bool            GSS_test_running_flag;
extern thread_reference_t       GSS_test_thread_p;
extern volatile uint64_t        GSS_cycle_count;

/* -------------------------------------------------------------------------
 * Shell command declarations
 * -------------------------------------------------------------------------*/

void cmd_GSS_test(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_GSS_cycles(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_measure_supply(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_measure_DUT(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_ID(BaseSequentialStream *chp, int argc, char *argv[]);

/* -------------------------------------------------------------------------
 * Module init
 * -------------------------------------------------------------------------*/

void GSS_init(void);

#endif /* GSS_H_ */
