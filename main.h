/*
 * main.h - GSS Control Software
 * STM32G474RE, ChibiOS 21.11
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "ch.h"
#include "hal.h"
#include "shell.h"
#include "chprintf.h"
#include "usbcfg.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ########################
// ##  Pin definitions   ##
// ########################

/* GPIOA */
#define GPIOA_RLC1              0U   /* PA0-PA7: relay control outputs (DUT select) */
#define GPIOA_RLC2              1U
#define GPIOA_RLC3              2U
#define GPIOA_RLC4              3U
#define GPIOA_RLC5              4U
#define GPIOA_RLC6              5U
#define GPIOA_RLC7              6U
#define GPIOA_RLC8              7U
#define GPIOA_AIN1              9U   /* PA9:  AIN1 (ADC analog input, supply +V) */
#define GPIOA_AIN2              10U  /* PA10: AIN2 (ADC analog input, supply -V) */
#define GPIOA_USB_DM            11U  /* PA11: USB D- */
#define GPIOA_USB_DP            12U  /* PA12: USB D+ */
#define GPIOA_SWDIO             13U  /* PA13: SWD data */
#define GPIOA_SWCLK             14U  /* PA14: SWD clock */

/* GPIOB */
#define GPIOB_ID0               0U   /* PB0-PB7: board serial number inputs */
#define GPIOB_ID1               1U
#define GPIOB_ID2               2U
#define GPIOB_ID3               3U
#define GPIOB_ID4               4U
#define GPIOB_ID5               5U
#define GPIOB_ID6               6U
#define GPIOB_ID7               7U
#define GPIOB_HRTIM_CHC1        12U  /* PB12: HRTIM CHC1 (PWM1, AF13) */
#define GPIOB_HRTIM_CHC2        13U  /* PB13: HRTIM CHC2 (PWM2, AF13) */
#define GPIOB_HRTIM_CHD1        14U  /* PB14: HRTIM CHD1 (PWM3, AF13) */
#define GPIOB_HRTIM_CHD2        15U  /* PB15: HRTIM CHD2 (PWM4, AF13) */

/* GPIOC */
#define GPIOC_LED_RED           0U   /* PC0: red LED   */
#define GPIOC_LED_GREEN         1U   /* PC1: green LED */
#define GPIOC_LED_BLUE          2U   /* PC2: blue LED  */
#define GPIOC_LED_YELLOW        3U   /* PC3: yellow LED */
#define GPIOC_HRTIM_CHF1        6U   /* PC6: HRTIM CHF1 (PWM7, AF13) */
#define GPIOC_HRTIM_CHF2        7U   /* PC7: HRTIM CHF2 (PWM8, AF13) */
#define GPIOC_HRTIM_CHE1        8U   /* PC8: HRTIM CHE1 (PWM5, AF13) */
#define GPIOC_HRTIM_CHE2        9U   /* PC9: HRTIM CHE2 (PWM6, AF13) */

// ########################
// ##  Global Variables  ##
// ########################

extern volatile bool clear_to_run_flag;

// ############################
// ## USB / Shell interfaces ##
// ############################

extern BaseSequentialStream *chp_USB;   /* defined in main.c */

/*
 * The STM32G4 USB peripheral has a BCDR register that controls DPPU (pull-up).
 * ChibiOS hal_usb_lld.h already defines usb_lld_connect_bus / disconnect_bus.
 * Do NOT redefine them here.
 */

// ###########################
// ## Function Declarations ##
// ###########################

void stop_test(void);

// #################################
// ##     Extern declarations     ##
// #################################

/* GSS test module */
extern void GSS_init(void);

extern void cmd_GSS_test(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_GSS_resume(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_GSS_cycles(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_measure_supply(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_measure_DUT(BaseSequentialStream *chp, int argc, char *argv[]);
extern void cmd_ID(BaseSequentialStream *chp, int argc, char *argv[]);

extern volatile bool GSS_test_running_flag;
extern thread_reference_t GSS_test_thread_p;

#endif /* MAIN_H_ */
