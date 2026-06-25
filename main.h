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
// ##  Global Variables  ##
// ########################

extern volatile bool clear_to_run_flag;
extern volatile bool GSS_error_flag;   /* set on any error; latched until reset */
extern volatile bool led_cmd_flag;     /* set by any command; cleared by LED thread */

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
