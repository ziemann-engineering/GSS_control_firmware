/*
    ChibiOS - Copyright (C) 2006..2020 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/*
 * GSS Control Board 1.0 - STM32G474RE
 * Pin assignments marked TBD will be filled in when PCB design is finalised.
 */

#ifndef BOARD_H
#define BOARD_H

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*
 * Setup for GSS Control Board 1.0 (STM32G474RE).
 */

/*
 * Board identifier.
 */
#define BOARD_GSS_CONTROL_1_0
#define BOARD_NAME                  "GSS Control Board 1.0"

/*
 * Board oscillators-related settings.
 * 20 MHz external crystal on PF0 (OSC_IN) / PF1 (OSC_OUT).
 */
#if !defined(STM32_LSECLK)
#define STM32_LSECLK                0U
#endif

#define STM32_LSEDRV                (3U << 3U)

#if !defined(STM32_HSECLK)
#define STM32_HSECLK                20000000U  /* 20 MHz crystal */
#endif

/*
 * MCU type as defined in the ST header.
 */
#define STM32G474xx

/*
 * IO pins assignments.
 *
 * GPIOA:
 *   PA0-PA7 - RLC1..RLC8 (output push-pull)  Relay control for DUT selection
 *   PA8     - AIN1        (analog)             Gate supply +V measurement (ADC5_IN1)
 *   PA9     - AIN2        (analog)             Gate supply -V measurement (ADC5_IN2)
 *   PA10    - unused      (analog)
 *   PA11    - USB_DM      (AF10)               USB D-
 *   PA12    - USB_DP      (AF10)               USB D+
 *   PA13    - SWDIO       (AF0, pull-up)        SWD data
 *   PA14    - SWCLK       (AF0, pull-down)      SWD clock
 *   PA15    - unused      (analog)
 */
#define GPIOA_RLC1                  0U
#define GPIOA_RLC2                  1U
#define GPIOA_RLC3                  2U
#define GPIOA_RLC4                  3U
#define GPIOA_RLC5                  4U
#define GPIOA_RLC6                  5U
#define GPIOA_RLC7                  6U
#define GPIOA_RLC8                  7U
#define GPIOA_AIN1                  8U
#define GPIOA_AIN2                  9U
#define GPIOA_PIN10                 10U
#define GPIOA_USB_DM                11U
#define GPIOA_USB_DP                12U
#define GPIOA_SWDIO                 13U
#define GPIOA_SWCLK                 14U
#define GPIOA_PIN15                 15U

/*
 * GPIOB:
 *   PB0-PB7  - ID0..ID7   (input, pull-down)  Board serial number
 *   PB8      - BOOT0      (analog)
 *   PB9-PB10 - unused     (analog)
 *   PB11    - GD_DIS      (output open-drain)  Gate driver disable, hardware pullup; low during switching
 *   PB12    - CHC1        (AF13)               HRTIM Timer C output 1 (PWM1)
 *   PB13    - CHC2        (AF13)               HRTIM Timer C output 2 (PWM2)
 *   PB14    - CHD1        (AF13)               HRTIM Timer D output 1 (PWM3)
 *   PB15    - CHD2        (AF13)               HRTIM Timer D output 2 (PWM4)
 */
#define GPIOB_ID0                   0U
#define GPIOB_ID1                   1U
#define GPIOB_ID2                   2U
#define GPIOB_ID3                   3U
#define GPIOB_ID4                   4U
#define GPIOB_ID5                   5U
#define GPIOB_ID6                   6U
#define GPIOB_ID7                   7U
#define GPIOB_PIN8                  8U
#define GPIOB_BOOT0_CTRL            8U   /* PB8 drives BOOT0 via capacitor C_BOOT */
#define GPIOB_PIN9                  9U
#define GPIOB_PIN10                 10U
#define GPIOB_GD_DIS                11U
#define GPIOB_HRTIM_CHC1            12U
#define GPIOB_HRTIM_CHC2            13U
#define GPIOB_HRTIM_CHD1            14U
#define GPIOB_HRTIM_CHD2            15U

/*
 * GPIOC:
 *   PC0     - LED_RED     (output push-pull)
 *   PC1     - LED_GREEN   (output push-pull)
 *   PC2     - LED_BLUE    (output push-pull)
 *   PC3     - LED_YELLOW  (output push-pull)
 *   PC4-PC5 - unused      (analog)
 *   PC6     - CHF1        (AF13)              HRTIM Timer F output 1 (PWM7)
 *   PC7     - CHF2        (AF13)              HRTIM Timer F output 2 (PWM8)
 *   PC8     - CHE1        (AF3)               HRTIM Timer E output 1 (PWM5)
 *   PC9     - CHE2        (AF3)               HRTIM Timer E output 2 (PWM6)
 *   PC10-PC13 - unused    (analog)
 *   PC14    - OSC32_IN    (analog)
 *   PC15    - OSC32_OUT   (analog)
 */
#define GPIOC_LED_RED               0U
#define GPIOC_LED_GREEN             1U
#define GPIOC_LED_BLUE              2U
#define GPIOC_LED_YELLOW            3U
#define GPIOC_PIN4                  4U
#define GPIOC_PIN5                  5U
#define GPIOC_HRTIM_CHF1            6U
#define GPIOC_HRTIM_CHF2            7U
#define GPIOC_HRTIM_CHE1            8U
#define GPIOC_HRTIM_CHE2            9U
#define GPIOC_PIN10                 10U
#define GPIOC_PIN11                 11U
#define GPIOC_PIN12                 12U
#define GPIOC_PIN13                 13U
#define GPIOC_OSC32_IN              14U
#define GPIOC_OSC32_OUT             15U

/* GPIOD: all TBD */
#define GPIOD_PIN0                  0U
#define GPIOD_PIN1                  1U
#define GPIOD_PIN2                  2U
#define GPIOD_PIN3                  3U
#define GPIOD_PIN4                  4U
#define GPIOD_PIN5                  5U
#define GPIOD_PIN6                  6U
#define GPIOD_PIN7                  7U
#define GPIOD_PIN8                  8U
#define GPIOD_PIN9                  9U
#define GPIOD_PIN10                 10U
#define GPIOD_PIN11                 11U
#define GPIOD_PIN12                 12U
#define GPIOD_PIN13                 13U
#define GPIOD_PIN14                 14U
#define GPIOD_PIN15                 15U

/* GPIOE: all TBD */
#define GPIOE_PIN0                  0U
#define GPIOE_PIN1                  1U
#define GPIOE_PIN2                  2U
#define GPIOE_PIN3                  3U
#define GPIOE_PIN4                  4U
#define GPIOE_PIN5                  5U
#define GPIOE_PIN6                  6U
#define GPIOE_PIN7                  7U
#define GPIOE_PIN8                  8U
#define GPIOE_PIN9                  9U
#define GPIOE_PIN10                 10U
#define GPIOE_PIN11                 11U
#define GPIOE_PIN12                 12U
#define GPIOE_PIN13                 13U
#define GPIOE_PIN14                 14U
#define GPIOE_PIN15                 15U

/* GPIOF: all TBD */
#define GPIOF_PIN0                  0U
#define GPIOF_PIN1                  1U
#define GPIOF_PIN2                  2U
#define GPIOF_PIN3                  3U
#define GPIOF_PIN4                  4U
#define GPIOF_PIN5                  5U
#define GPIOF_PIN6                  6U
#define GPIOF_PIN7                  7U
#define GPIOF_PIN8                  8U
#define GPIOF_PIN9                  9U
#define GPIOF_PIN10                 10U
#define GPIOF_PIN11                 11U
#define GPIOF_PIN12                 12U
#define GPIOF_PIN13                 13U
#define GPIOF_PIN14                 14U
#define GPIOF_PIN15                 15U

/* GPIOG: all TBD */
#define GPIOG_PIN0                  0U
#define GPIOG_PIN1                  1U
#define GPIOG_PIN2                  2U
#define GPIOG_PIN3                  3U
#define GPIOG_PIN4                  4U
#define GPIOG_PIN5                  5U
#define GPIOG_PIN6                  6U
#define GPIOG_PIN7                  7U
#define GPIOG_PIN8                  8U
#define GPIOG_PIN9                  9U
#define GPIOG_PIN10                 10U
#define GPIOG_PIN11                 11U
#define GPIOG_PIN12                 12U
#define GPIOG_PIN13                 13U
#define GPIOG_PIN14                 14U
#define GPIOG_PIN15                 15U

/* GPIOH: only PH0/PH1 on STM32G474RE (OSC_IN/OUT, unused) */
#define GPIOH_PIN0                  0U
#define GPIOH_PIN1                  1U

/*
 * IO lines assignments.
 */
#define LINE_AIN1                   PAL_LINE(GPIOA,  8U)
#define LINE_AIN2                   PAL_LINE(GPIOA,  9U)
#define LINE_USB_DM                 PAL_LINE(GPIOA, 11U)
#define LINE_USB_DP                 PAL_LINE(GPIOA, 12U)
#define LINE_SWDIO                  PAL_LINE(GPIOA, 13U)
#define LINE_SWCLK                  PAL_LINE(GPIOA, 14U)
#define LINE_SWO                    PAL_LINE(GPIOB,  3U)
#define LINE_GD_DIS                 PAL_LINE(GPIOB, 11U)

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*
 * I/O ports initial setup, this configuration is established soon after reset
 * in the initialization code.
 * Please refer to the STM32 Reference Manual for details.
 */
#define PIN_MODE_INPUT(n)           (0U << ((n) * 2U))
#define PIN_MODE_OUTPUT(n)          (1U << ((n) * 2U))
#define PIN_MODE_ALTERNATE(n)       (2U << ((n) * 2U))
#define PIN_MODE_ANALOG(n)          (3U << ((n) * 2U))
#define PIN_ODR_LOW(n)              (0U << (n))
#define PIN_ODR_HIGH(n)             (1U << (n))
#define PIN_OTYPE_PUSHPULL(n)       (0U << (n))
#define PIN_OTYPE_OPENDRAIN(n)      (1U << (n))
#define PIN_OSPEED_VERYLOW(n)       (0U << ((n) * 2U))
#define PIN_OSPEED_LOW(n)           (1U << ((n) * 2U))
#define PIN_OSPEED_MEDIUM(n)        (2U << ((n) * 2U))
#define PIN_OSPEED_HIGH(n)          (3U << ((n) * 2U))
#define PIN_PUPDR_FLOATING(n)       (0U << ((n) * 2U))
#define PIN_PUPDR_PULLUP(n)         (1U << ((n) * 2U))
#define PIN_PUPDR_PULLDOWN(n)       (2U << ((n) * 2U))
#define PIN_AFIO_AF(n, v)           ((v) << (((n) % 8U) * 4U))
#define PIN_ASCR_DISABLED(n)        (0U << (n))
#define PIN_ASCR_ENABLED(n)         (1U << (n))
#define PIN_LOCKR_DISABLED(n)       (0U << (n))
#define PIN_LOCKR_ENABLED(n)        (1U << (n))

/*
 * Helper macros for unconfigured (TBD) pins: analog input, no pull, ODR=0.
 */
#define PIN_TBD_MODE(n)             PIN_MODE_ANALOG(n)
#define PIN_TBD_OTYPE(n)            PIN_OTYPE_PUSHPULL(n)
#define PIN_TBD_OSPEED(n)           PIN_OSPEED_VERYLOW(n)
#define PIN_TBD_PUPDR(n)            PIN_PUPDR_FLOATING(n)
#define PIN_TBD_ODR(n)              PIN_ODR_LOW(n)
#define PIN_TBD_AF(n)               PIN_AFIO_AF(n, 0U)

/*
 * GPIOA setup:
 *   PA0-PA7  output PP (RLC relay control, DUT select)
 *   PA8      analog (AIN1 supply measurement, ADC5_IN1)
 *   PA9      analog (AIN2 supply measurement, ADC5_IN2)
 *   PA10     analog (unused)
 *   PA11     AF10 PP very-high (USB_DM)
 *   PA12     AF10 PP very-high (USB_DP)
 *   PA13     AF0  PP very-high pull-up (SWDIO)
 *   PA14     AF0  PP very-high pull-down (SWCLK)
 *   PA15     analog (unused)
 */
#define VAL_GPIOA_MODER             (PIN_MODE_OUTPUT(GPIOA_RLC1) |          \
                                     PIN_MODE_OUTPUT(GPIOA_RLC2) |          \
                                     PIN_MODE_OUTPUT(GPIOA_RLC3) |          \
                                     PIN_MODE_OUTPUT(GPIOA_RLC4) |          \
                                     PIN_MODE_OUTPUT(GPIOA_RLC5) |          \
                                     PIN_MODE_OUTPUT(GPIOA_RLC6) |          \
                                     PIN_MODE_OUTPUT(GPIOA_RLC7) |          \
                                     PIN_MODE_OUTPUT(GPIOA_RLC8) |          \
                                     PIN_MODE_ANALOG(GPIOA_AIN1) |          \
                                     PIN_MODE_ANALOG(GPIOA_AIN2) |          \
                                     PIN_MODE_ANALOG(GPIOA_PIN10) |         \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_DM) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_USB_DP) |     \
                                     PIN_MODE_ALTERNATE(GPIOA_SWDIO) |      \
                                     PIN_MODE_ALTERNATE(GPIOA_SWCLK) |      \
                                     PIN_MODE_ANALOG(GPIOA_PIN15))
#define VAL_GPIOA_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOA_RLC1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RLC2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RLC3) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RLC4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RLC5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RLC6) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RLC7) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_RLC8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_AIN1) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_AIN2) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_DM) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_USB_DP) |     \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWDIO) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_SWCLK) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOA_PIN15))
#define VAL_GPIOA_OSPEEDR           (PIN_OSPEED_MEDIUM(GPIOA_RLC1) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_RLC2) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_RLC3) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_RLC4) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_RLC5) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_RLC6) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_RLC7) |        \
                                     PIN_OSPEED_MEDIUM(GPIOA_RLC8) |        \
                                     PIN_OSPEED_VERYLOW(GPIOA_AIN1) |       \
                                     PIN_OSPEED_VERYLOW(GPIOA_AIN2) |       \
                                     PIN_OSPEED_VERYLOW(GPIOA_PIN10) |      \
                                     PIN_OSPEED_HIGH(GPIOA_USB_DM) |        \
                                     PIN_OSPEED_HIGH(GPIOA_USB_DP) |        \
                                     PIN_OSPEED_HIGH(GPIOA_SWDIO) |         \
                                     PIN_OSPEED_HIGH(GPIOA_SWCLK) |         \
                                     PIN_OSPEED_VERYLOW(GPIOA_PIN15))
#define VAL_GPIOA_PUPDR             (PIN_PUPDR_FLOATING(GPIOA_RLC1) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_RLC2) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_RLC3) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_RLC4) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_RLC5) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_RLC6) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_RLC7) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_RLC8) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_AIN1) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_AIN2) |       \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_DM) |     \
                                     PIN_PUPDR_FLOATING(GPIOA_USB_DP) |     \
                                     PIN_PUPDR_PULLUP(GPIOA_SWDIO) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOA_SWCLK) |      \
                                     PIN_PUPDR_FLOATING(GPIOA_PIN15))
#define VAL_GPIOA_ODR               (PIN_ODR_LOW(GPIOA_RLC1) |              \
                                     PIN_ODR_LOW(GPIOA_RLC2) |              \
                                     PIN_ODR_LOW(GPIOA_RLC3) |              \
                                     PIN_ODR_LOW(GPIOA_RLC4) |              \
                                     PIN_ODR_LOW(GPIOA_RLC5) |              \
                                     PIN_ODR_LOW(GPIOA_RLC6) |              \
                                     PIN_ODR_LOW(GPIOA_RLC7) |              \
                                     PIN_ODR_LOW(GPIOA_RLC8) |              \
                                     PIN_ODR_LOW(GPIOA_AIN1) |              \
                                     PIN_ODR_LOW(GPIOA_AIN2) |              \
                                     PIN_ODR_LOW(GPIOA_PIN10) |             \
                                     PIN_ODR_LOW(GPIOA_USB_DM) |            \
                                     PIN_ODR_LOW(GPIOA_USB_DP) |            \
                                     PIN_ODR_HIGH(GPIOA_SWDIO) |            \
                                     PIN_ODR_HIGH(GPIOA_SWCLK) |            \
                                     PIN_ODR_LOW(GPIOA_PIN15))
#define VAL_GPIOA_AFRL              (PIN_AFIO_AF(GPIOA_RLC1,  0U) |         \
                                     PIN_AFIO_AF(GPIOA_RLC2,  0U) |         \
                                     PIN_AFIO_AF(GPIOA_RLC3,  0U) |         \
                                     PIN_AFIO_AF(GPIOA_RLC4,  0U) |         \
                                     PIN_AFIO_AF(GPIOA_RLC5,  0U) |         \
                                     PIN_AFIO_AF(GPIOA_RLC6,  0U) |         \
                                     PIN_AFIO_AF(GPIOA_RLC7,  0U) |         \
                                     PIN_AFIO_AF(GPIOA_RLC8,  0U))
#define VAL_GPIOA_AFRH              (PIN_AFIO_AF(GPIOA_AIN1,   0U) |        \
                                     PIN_AFIO_AF(GPIOA_AIN2,   0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN10,  0U) |        \
                                     PIN_AFIO_AF(GPIOA_USB_DM, 10U) |       \
                                     PIN_AFIO_AF(GPIOA_USB_DP, 10U) |       \
                                     PIN_AFIO_AF(GPIOA_SWDIO,  0U) |        \
                                     PIN_AFIO_AF(GPIOA_SWCLK,  0U) |        \
                                     PIN_AFIO_AF(GPIOA_PIN15,  0U))

/*
 * GPIOB setup:
 *   PB0-PB7  input pull-down (ID0..ID7 board serial number)
 *   PB8-PB10 analog (unused)
 *   PB11     output OD floating (GD_DIS, hardware pullup; high=hi-Z/enabled, low=disabled)
 *   PB12     AF13 PP very-high (HRTIM CHC1)
 *   PB13     AF13 PP very-high (HRTIM CHC2)
 *   PB14     AF13 PP very-high (HRTIM CHD1)
 *   PB15     AF13 PP very-high (HRTIM CHD2)
 */
#define VAL_GPIOB_MODER             (PIN_MODE_INPUT(GPIOB_ID0) |            \
                                     PIN_MODE_INPUT(GPIOB_ID1) |            \
                                     PIN_MODE_INPUT(GPIOB_ID2) |            \
                                     PIN_MODE_INPUT(GPIOB_ID3) |            \
                                     PIN_MODE_INPUT(GPIOB_ID4) |            \
                                     PIN_MODE_INPUT(GPIOB_ID5) |            \
                                     PIN_MODE_INPUT(GPIOB_ID6) |            \
                                     PIN_MODE_INPUT(GPIOB_ID7) |            \
                                     PIN_MODE_ANALOG(GPIOB_PIN8) |          \
                                     PIN_MODE_ANALOG(GPIOB_PIN9) |          \
                                     PIN_MODE_ANALOG(GPIOB_PIN10) |         \
                                     PIN_MODE_OUTPUT(GPIOB_GD_DIS) |        \
                                     PIN_MODE_ALTERNATE(GPIOB_HRTIM_CHC1) | \
                                     PIN_MODE_ALTERNATE(GPIOB_HRTIM_CHC2) | \
                                     PIN_MODE_ALTERNATE(GPIOB_HRTIM_CHD1) | \
                                     PIN_MODE_ALTERNATE(GPIOB_HRTIM_CHD2))
#define VAL_GPIOB_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOB_ID0) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ID1) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ID2) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ID3) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ID4) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ID5) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ID6) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_ID7) |        \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN8) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN9) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOB_PIN10) |      \
                                     PIN_OTYPE_OPENDRAIN(GPIOB_GD_DIS) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOB_HRTIM_CHC1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_HRTIM_CHC2) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_HRTIM_CHD1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOB_HRTIM_CHD2))
#define VAL_GPIOB_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOB_ID0) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_ID1) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_ID2) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_ID3) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_ID4) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_ID5) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_ID6) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_ID7) |        \
                                     PIN_OSPEED_VERYLOW(GPIOB_PIN8) |       \
                                     PIN_OSPEED_VERYLOW(GPIOB_PIN9) |       \
                                     PIN_OSPEED_VERYLOW(GPIOB_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOB_GD_DIS) |     \
                                     PIN_OSPEED_HIGH(GPIOB_HRTIM_CHC1) |    \
                                     PIN_OSPEED_HIGH(GPIOB_HRTIM_CHC2) |    \
                                     PIN_OSPEED_HIGH(GPIOB_HRTIM_CHD1) |    \
                                     PIN_OSPEED_HIGH(GPIOB_HRTIM_CHD2))
#define VAL_GPIOB_PUPDR             (PIN_PUPDR_PULLDOWN(GPIOB_ID0) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ID1) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ID2) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ID3) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ID4) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ID5) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ID6) |        \
                                     PIN_PUPDR_PULLDOWN(GPIOB_ID7) |        \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN8) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN9) |       \
                                     PIN_PUPDR_FLOATING(GPIOB_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOB_GD_DIS) |     \
                                     PIN_PUPDR_FLOATING(GPIOB_HRTIM_CHC1) | \
                                     PIN_PUPDR_FLOATING(GPIOB_HRTIM_CHC2) | \
                                     PIN_PUPDR_FLOATING(GPIOB_HRTIM_CHD1) | \
                                     PIN_PUPDR_FLOATING(GPIOB_HRTIM_CHD2))
#define VAL_GPIOB_ODR               (PIN_ODR_LOW(GPIOB_ID0) |               \
                                     PIN_ODR_LOW(GPIOB_ID1) |               \
                                     PIN_ODR_LOW(GPIOB_ID2) |               \
                                     PIN_ODR_LOW(GPIOB_ID3) |               \
                                     PIN_ODR_LOW(GPIOB_ID4) |               \
                                     PIN_ODR_LOW(GPIOB_ID5) |               \
                                     PIN_ODR_LOW(GPIOB_ID6) |               \
                                     PIN_ODR_LOW(GPIOB_ID7) |               \
                                     PIN_ODR_LOW(GPIOB_PIN8) |              \
                                     PIN_ODR_LOW(GPIOB_PIN9) |              \
                                     PIN_ODR_LOW(GPIOB_PIN10) |             \
                                     PIN_ODR_HIGH(GPIOB_GD_DIS) |           \
                                     PIN_ODR_LOW(GPIOB_HRTIM_CHC1) |        \
                                     PIN_ODR_LOW(GPIOB_HRTIM_CHC2) |        \
                                     PIN_ODR_LOW(GPIOB_HRTIM_CHD1) |        \
                                     PIN_ODR_LOW(GPIOB_HRTIM_CHD2))
#define VAL_GPIOB_AFRL              (PIN_AFIO_AF(GPIOB_ID0,  0U) |          \
                                     PIN_AFIO_AF(GPIOB_ID1,  0U) |          \
                                     PIN_AFIO_AF(GPIOB_ID2,  0U) |          \
                                     PIN_AFIO_AF(GPIOB_ID3,  0U) |          \
                                     PIN_AFIO_AF(GPIOB_ID4,  0U) |          \
                                     PIN_AFIO_AF(GPIOB_ID5,  0U) |          \
                                     PIN_AFIO_AF(GPIOB_ID6,  0U) |          \
                                     PIN_AFIO_AF(GPIOB_ID7,  0U))
#define VAL_GPIOB_AFRH              (PIN_AFIO_AF(GPIOB_PIN8,         0U) |  \
                                     PIN_AFIO_AF(GPIOB_PIN9,         0U) |  \
                                     PIN_AFIO_AF(GPIOB_PIN10,        0U) |  \
                                     PIN_AFIO_AF(GPIOB_GD_DIS,       0U) |  \
                                     PIN_AFIO_AF(GPIOB_HRTIM_CHC1,  13U) | \
                                     PIN_AFIO_AF(GPIOB_HRTIM_CHC2,  13U) | \
                                     PIN_AFIO_AF(GPIOB_HRTIM_CHD1,  13U) | \
                                     PIN_AFIO_AF(GPIOB_HRTIM_CHD2,  13U))

/*
 * GPIOC setup:
 *   PC0-PC3  output PP low-speed (LED red/green/blue/yellow)
 *   PC4-PC5  analog (unused)
 *   PC6      AF13 PP very-high (HRTIM CHF1)
 *   PC7      AF13 PP very-high (HRTIM CHF2)
 *   PC8      AF3  PP very-high (HRTIM CHE1)
 *   PC9      AF3  PP very-high (HRTIM CHE2)
 *   PC10-PC15 analog (unused / OSC32)
 */
#define VAL_GPIOC_MODER             (PIN_MODE_OUTPUT(GPIOC_LED_RED) |       \
                                     PIN_MODE_OUTPUT(GPIOC_LED_GREEN) |     \
                                     PIN_MODE_OUTPUT(GPIOC_LED_BLUE) |      \
                                     PIN_MODE_OUTPUT(GPIOC_LED_YELLOW) |    \
                                     PIN_MODE_ANALOG(GPIOC_PIN4) |          \
                                     PIN_MODE_ANALOG(GPIOC_PIN5) |          \
                                     PIN_MODE_ALTERNATE(GPIOC_HRTIM_CHF1) | \
                                     PIN_MODE_ALTERNATE(GPIOC_HRTIM_CHF2) | \
                                     PIN_MODE_ALTERNATE(GPIOC_HRTIM_CHE1) | \
                                     PIN_MODE_ALTERNATE(GPIOC_HRTIM_CHE2) | \
                                     PIN_MODE_ANALOG(GPIOC_PIN10) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN11) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN12) |         \
                                     PIN_MODE_ANALOG(GPIOC_PIN13) |         \
                                     PIN_MODE_ANALOG(GPIOC_OSC32_IN) |      \
                                     PIN_MODE_ANALOG(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OTYPER            (PIN_OTYPE_PUSHPULL(GPIOC_LED_RED) |    \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED_GREEN) |  \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED_BLUE) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_LED_YELLOW) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN4) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN5) |       \
                                     PIN_OTYPE_PUSHPULL(GPIOC_HRTIM_CHF1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_HRTIM_CHF2) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_HRTIM_CHE1) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_HRTIM_CHE2) | \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN10) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN11) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN12) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_PIN13) |      \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_IN) |   \
                                     PIN_OTYPE_PUSHPULL(GPIOC_OSC32_OUT))
#define VAL_GPIOC_OSPEEDR           (PIN_OSPEED_VERYLOW(GPIOC_LED_RED) |   \
                                     PIN_OSPEED_VERYLOW(GPIOC_LED_GREEN) |  \
                                     PIN_OSPEED_VERYLOW(GPIOC_LED_BLUE) |   \
                                     PIN_OSPEED_VERYLOW(GPIOC_LED_YELLOW) | \
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN4) |       \
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN5) |       \
                                     PIN_OSPEED_HIGH(GPIOC_HRTIM_CHF1) |    \
                                     PIN_OSPEED_HIGH(GPIOC_HRTIM_CHF2) |    \
                                     PIN_OSPEED_HIGH(GPIOC_HRTIM_CHE1) |    \
                                     PIN_OSPEED_HIGH(GPIOC_HRTIM_CHE2) |    \
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN10) |      \
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN11) |      \
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN12) |      \
                                     PIN_OSPEED_VERYLOW(GPIOC_PIN13) |      \
                                     PIN_OSPEED_VERYLOW(GPIOC_OSC32_IN) |   \
                                     PIN_OSPEED_VERYLOW(GPIOC_OSC32_OUT))
#define VAL_GPIOC_PUPDR             (PIN_PUPDR_FLOATING(GPIOC_LED_RED) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_LED_GREEN) |  \
                                     PIN_PUPDR_FLOATING(GPIOC_LED_BLUE) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_LED_YELLOW) | \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN4) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN5) |       \
                                     PIN_PUPDR_FLOATING(GPIOC_HRTIM_CHF1) | \
                                     PIN_PUPDR_FLOATING(GPIOC_HRTIM_CHF2) | \
                                     PIN_PUPDR_FLOATING(GPIOC_HRTIM_CHE1) | \
                                     PIN_PUPDR_FLOATING(GPIOC_HRTIM_CHE2) | \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN10) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN11) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN12) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_PIN13) |      \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_IN) |   \
                                     PIN_PUPDR_FLOATING(GPIOC_OSC32_OUT))
#define VAL_GPIOC_ODR               (PIN_ODR_LOW(GPIOC_LED_RED) |          \
                                     PIN_ODR_LOW(GPIOC_LED_GREEN) |         \
                                     PIN_ODR_LOW(GPIOC_LED_BLUE) |          \
                                     PIN_ODR_LOW(GPIOC_LED_YELLOW) |        \
                                     PIN_ODR_LOW(GPIOC_PIN4) |              \
                                     PIN_ODR_LOW(GPIOC_PIN5) |              \
                                     PIN_ODR_LOW(GPIOC_HRTIM_CHF1) |        \
                                     PIN_ODR_LOW(GPIOC_HRTIM_CHF2) |        \
                                     PIN_ODR_LOW(GPIOC_HRTIM_CHE1) |        \
                                     PIN_ODR_LOW(GPIOC_HRTIM_CHE2) |        \
                                     PIN_ODR_LOW(GPIOC_PIN10) |             \
                                     PIN_ODR_LOW(GPIOC_PIN11) |             \
                                     PIN_ODR_LOW(GPIOC_PIN12) |             \
                                     PIN_ODR_LOW(GPIOC_PIN13) |             \
                                     PIN_ODR_LOW(GPIOC_OSC32_IN) |          \
                                     PIN_ODR_LOW(GPIOC_OSC32_OUT))
#define VAL_GPIOC_AFRL              (PIN_AFIO_AF(GPIOC_LED_RED,      0U) |  \
                                     PIN_AFIO_AF(GPIOC_LED_GREEN,    0U) |  \
                                     PIN_AFIO_AF(GPIOC_LED_BLUE,     0U) |  \
                                     PIN_AFIO_AF(GPIOC_LED_YELLOW,   0U) |  \
                                     PIN_AFIO_AF(GPIOC_PIN4,         0U) |  \
                                     PIN_AFIO_AF(GPIOC_PIN5,         0U) |  \
                                     PIN_AFIO_AF(GPIOC_HRTIM_CHF1,  13U) | \
                                     PIN_AFIO_AF(GPIOC_HRTIM_CHF2,  13U))
#define VAL_GPIOC_AFRH              (PIN_AFIO_AF(GPIOC_HRTIM_CHE1,   3U) | \
                                     PIN_AFIO_AF(GPIOC_HRTIM_CHE2,   3U) | \
                                     PIN_AFIO_AF(GPIOC_PIN10,        0U) |  \
                                     PIN_AFIO_AF(GPIOC_PIN11,        0U) |  \
                                     PIN_AFIO_AF(GPIOC_PIN12,        0U) |  \
                                     PIN_AFIO_AF(GPIOC_PIN13,        0U) |  \
                                     PIN_AFIO_AF(GPIOC_OSC32_IN,     0U) |  \
                                     PIN_AFIO_AF(GPIOC_OSC32_OUT,    0U))

/*
 * GPIOD setup: all TBD (analog).
 */
#define VAL_GPIOD_MODER             (PIN_TBD_MODE(GPIOD_PIN0) |             \
                                     PIN_TBD_MODE(GPIOD_PIN1) |             \
                                     PIN_TBD_MODE(GPIOD_PIN2) |             \
                                     PIN_TBD_MODE(GPIOD_PIN3) |             \
                                     PIN_TBD_MODE(GPIOD_PIN4) |             \
                                     PIN_TBD_MODE(GPIOD_PIN5) |             \
                                     PIN_TBD_MODE(GPIOD_PIN6) |             \
                                     PIN_TBD_MODE(GPIOD_PIN7) |             \
                                     PIN_TBD_MODE(GPIOD_PIN8) |             \
                                     PIN_TBD_MODE(GPIOD_PIN9) |             \
                                     PIN_TBD_MODE(GPIOD_PIN10) |            \
                                     PIN_TBD_MODE(GPIOD_PIN11) |            \
                                     PIN_TBD_MODE(GPIOD_PIN12) |            \
                                     PIN_TBD_MODE(GPIOD_PIN13) |            \
                                     PIN_TBD_MODE(GPIOD_PIN14) |            \
                                     PIN_TBD_MODE(GPIOD_PIN15))
#define VAL_GPIOD_OTYPER            (PIN_TBD_OTYPE(GPIOD_PIN0) |            \
                                     PIN_TBD_OTYPE(GPIOD_PIN1) |            \
                                     PIN_TBD_OTYPE(GPIOD_PIN2) |            \
                                     PIN_TBD_OTYPE(GPIOD_PIN3) |            \
                                     PIN_TBD_OTYPE(GPIOD_PIN4) |            \
                                     PIN_TBD_OTYPE(GPIOD_PIN5) |            \
                                     PIN_TBD_OTYPE(GPIOD_PIN6) |            \
                                     PIN_TBD_OTYPE(GPIOD_PIN7) |            \
                                     PIN_TBD_OTYPE(GPIOD_PIN8) |            \
                                     PIN_TBD_OTYPE(GPIOD_PIN9) |            \
                                     PIN_TBD_OTYPE(GPIOD_PIN10) |           \
                                     PIN_TBD_OTYPE(GPIOD_PIN11) |           \
                                     PIN_TBD_OTYPE(GPIOD_PIN12) |           \
                                     PIN_TBD_OTYPE(GPIOD_PIN13) |           \
                                     PIN_TBD_OTYPE(GPIOD_PIN14) |           \
                                     PIN_TBD_OTYPE(GPIOD_PIN15))
#define VAL_GPIOD_OSPEEDR           (PIN_TBD_OSPEED(GPIOD_PIN0) |           \
                                     PIN_TBD_OSPEED(GPIOD_PIN1) |           \
                                     PIN_TBD_OSPEED(GPIOD_PIN2) |           \
                                     PIN_TBD_OSPEED(GPIOD_PIN3) |           \
                                     PIN_TBD_OSPEED(GPIOD_PIN4) |           \
                                     PIN_TBD_OSPEED(GPIOD_PIN5) |           \
                                     PIN_TBD_OSPEED(GPIOD_PIN6) |           \
                                     PIN_TBD_OSPEED(GPIOD_PIN7) |           \
                                     PIN_TBD_OSPEED(GPIOD_PIN8) |           \
                                     PIN_TBD_OSPEED(GPIOD_PIN9) |           \
                                     PIN_TBD_OSPEED(GPIOD_PIN10) |          \
                                     PIN_TBD_OSPEED(GPIOD_PIN11) |          \
                                     PIN_TBD_OSPEED(GPIOD_PIN12) |          \
                                     PIN_TBD_OSPEED(GPIOD_PIN13) |          \
                                     PIN_TBD_OSPEED(GPIOD_PIN14) |          \
                                     PIN_TBD_OSPEED(GPIOD_PIN15))
#define VAL_GPIOD_PUPDR             (PIN_TBD_PUPDR(GPIOD_PIN0) |            \
                                     PIN_TBD_PUPDR(GPIOD_PIN1) |            \
                                     PIN_TBD_PUPDR(GPIOD_PIN2) |            \
                                     PIN_TBD_PUPDR(GPIOD_PIN3) |            \
                                     PIN_TBD_PUPDR(GPIOD_PIN4) |            \
                                     PIN_TBD_PUPDR(GPIOD_PIN5) |            \
                                     PIN_TBD_PUPDR(GPIOD_PIN6) |            \
                                     PIN_TBD_PUPDR(GPIOD_PIN7) |            \
                                     PIN_TBD_PUPDR(GPIOD_PIN8) |            \
                                     PIN_TBD_PUPDR(GPIOD_PIN9) |            \
                                     PIN_TBD_PUPDR(GPIOD_PIN10) |           \
                                     PIN_TBD_PUPDR(GPIOD_PIN11) |           \
                                     PIN_TBD_PUPDR(GPIOD_PIN12) |           \
                                     PIN_TBD_PUPDR(GPIOD_PIN13) |           \
                                     PIN_TBD_PUPDR(GPIOD_PIN14) |           \
                                     PIN_TBD_PUPDR(GPIOD_PIN15))
#define VAL_GPIOD_ODR               (PIN_TBD_ODR(GPIOD_PIN0) |              \
                                     PIN_TBD_ODR(GPIOD_PIN1) |              \
                                     PIN_TBD_ODR(GPIOD_PIN2) |              \
                                     PIN_TBD_ODR(GPIOD_PIN3) |              \
                                     PIN_TBD_ODR(GPIOD_PIN4) |              \
                                     PIN_TBD_ODR(GPIOD_PIN5) |              \
                                     PIN_TBD_ODR(GPIOD_PIN6) |              \
                                     PIN_TBD_ODR(GPIOD_PIN7) |              \
                                     PIN_TBD_ODR(GPIOD_PIN8) |              \
                                     PIN_TBD_ODR(GPIOD_PIN9) |              \
                                     PIN_TBD_ODR(GPIOD_PIN10) |             \
                                     PIN_TBD_ODR(GPIOD_PIN11) |             \
                                     PIN_TBD_ODR(GPIOD_PIN12) |             \
                                     PIN_TBD_ODR(GPIOD_PIN13) |             \
                                     PIN_TBD_ODR(GPIOD_PIN14) |             \
                                     PIN_TBD_ODR(GPIOD_PIN15))
#define VAL_GPIOD_AFRL              (PIN_TBD_AF(GPIOD_PIN0) |               \
                                     PIN_TBD_AF(GPIOD_PIN1) |               \
                                     PIN_TBD_AF(GPIOD_PIN2) |               \
                                     PIN_TBD_AF(GPIOD_PIN3) |               \
                                     PIN_TBD_AF(GPIOD_PIN4) |               \
                                     PIN_TBD_AF(GPIOD_PIN5) |               \
                                     PIN_TBD_AF(GPIOD_PIN6) |               \
                                     PIN_TBD_AF(GPIOD_PIN7))
#define VAL_GPIOD_AFRH              (PIN_TBD_AF(GPIOD_PIN8) |               \
                                     PIN_TBD_AF(GPIOD_PIN9) |               \
                                     PIN_TBD_AF(GPIOD_PIN10) |              \
                                     PIN_TBD_AF(GPIOD_PIN11) |              \
                                     PIN_TBD_AF(GPIOD_PIN12) |              \
                                     PIN_TBD_AF(GPIOD_PIN13) |              \
                                     PIN_TBD_AF(GPIOD_PIN14) |              \
                                     PIN_TBD_AF(GPIOD_PIN15))

/*
 * GPIOE setup: all TBD (analog).
 */
#define VAL_GPIOE_MODER             (PIN_TBD_MODE(GPIOE_PIN0) |             \
                                     PIN_TBD_MODE(GPIOE_PIN1) |             \
                                     PIN_TBD_MODE(GPIOE_PIN2) |             \
                                     PIN_TBD_MODE(GPIOE_PIN3) |             \
                                     PIN_TBD_MODE(GPIOE_PIN4) |             \
                                     PIN_TBD_MODE(GPIOE_PIN5) |             \
                                     PIN_TBD_MODE(GPIOE_PIN6) |             \
                                     PIN_TBD_MODE(GPIOE_PIN7) |             \
                                     PIN_TBD_MODE(GPIOE_PIN8) |             \
                                     PIN_TBD_MODE(GPIOE_PIN9) |             \
                                     PIN_TBD_MODE(GPIOE_PIN10) |            \
                                     PIN_TBD_MODE(GPIOE_PIN11) |            \
                                     PIN_TBD_MODE(GPIOE_PIN12) |            \
                                     PIN_TBD_MODE(GPIOE_PIN13) |            \
                                     PIN_TBD_MODE(GPIOE_PIN14) |            \
                                     PIN_TBD_MODE(GPIOE_PIN15))
#define VAL_GPIOE_OTYPER            (PIN_TBD_OTYPE(GPIOE_PIN0) |            \
                                     PIN_TBD_OTYPE(GPIOE_PIN1) |            \
                                     PIN_TBD_OTYPE(GPIOE_PIN2) |            \
                                     PIN_TBD_OTYPE(GPIOE_PIN3) |            \
                                     PIN_TBD_OTYPE(GPIOE_PIN4) |            \
                                     PIN_TBD_OTYPE(GPIOE_PIN5) |            \
                                     PIN_TBD_OTYPE(GPIOE_PIN6) |            \
                                     PIN_TBD_OTYPE(GPIOE_PIN7) |            \
                                     PIN_TBD_OTYPE(GPIOE_PIN8) |            \
                                     PIN_TBD_OTYPE(GPIOE_PIN9) |            \
                                     PIN_TBD_OTYPE(GPIOE_PIN10) |           \
                                     PIN_TBD_OTYPE(GPIOE_PIN11) |           \
                                     PIN_TBD_OTYPE(GPIOE_PIN12) |           \
                                     PIN_TBD_OTYPE(GPIOE_PIN13) |           \
                                     PIN_TBD_OTYPE(GPIOE_PIN14) |           \
                                     PIN_TBD_OTYPE(GPIOE_PIN15))
#define VAL_GPIOE_OSPEEDR           (PIN_TBD_OSPEED(GPIOE_PIN0) |           \
                                     PIN_TBD_OSPEED(GPIOE_PIN1) |           \
                                     PIN_TBD_OSPEED(GPIOE_PIN2) |           \
                                     PIN_TBD_OSPEED(GPIOE_PIN3) |           \
                                     PIN_TBD_OSPEED(GPIOE_PIN4) |           \
                                     PIN_TBD_OSPEED(GPIOE_PIN5) |           \
                                     PIN_TBD_OSPEED(GPIOE_PIN6) |           \
                                     PIN_TBD_OSPEED(GPIOE_PIN7) |           \
                                     PIN_TBD_OSPEED(GPIOE_PIN8) |           \
                                     PIN_TBD_OSPEED(GPIOE_PIN9) |           \
                                     PIN_TBD_OSPEED(GPIOE_PIN10) |          \
                                     PIN_TBD_OSPEED(GPIOE_PIN11) |          \
                                     PIN_TBD_OSPEED(GPIOE_PIN12) |          \
                                     PIN_TBD_OSPEED(GPIOE_PIN13) |          \
                                     PIN_TBD_OSPEED(GPIOE_PIN14) |          \
                                     PIN_TBD_OSPEED(GPIOE_PIN15))
#define VAL_GPIOE_PUPDR             (PIN_TBD_PUPDR(GPIOE_PIN0) |            \
                                     PIN_TBD_PUPDR(GPIOE_PIN1) |            \
                                     PIN_TBD_PUPDR(GPIOE_PIN2) |            \
                                     PIN_TBD_PUPDR(GPIOE_PIN3) |            \
                                     PIN_TBD_PUPDR(GPIOE_PIN4) |            \
                                     PIN_TBD_PUPDR(GPIOE_PIN5) |            \
                                     PIN_TBD_PUPDR(GPIOE_PIN6) |            \
                                     PIN_TBD_PUPDR(GPIOE_PIN7) |            \
                                     PIN_TBD_PUPDR(GPIOE_PIN8) |            \
                                     PIN_TBD_PUPDR(GPIOE_PIN9) |            \
                                     PIN_TBD_PUPDR(GPIOE_PIN10) |           \
                                     PIN_TBD_PUPDR(GPIOE_PIN11) |           \
                                     PIN_TBD_PUPDR(GPIOE_PIN12) |           \
                                     PIN_TBD_PUPDR(GPIOE_PIN13) |           \
                                     PIN_TBD_PUPDR(GPIOE_PIN14) |           \
                                     PIN_TBD_PUPDR(GPIOE_PIN15))
#define VAL_GPIOE_ODR               (PIN_TBD_ODR(GPIOE_PIN0) |              \
                                     PIN_TBD_ODR(GPIOE_PIN1) |              \
                                     PIN_TBD_ODR(GPIOE_PIN2) |              \
                                     PIN_TBD_ODR(GPIOE_PIN3) |              \
                                     PIN_TBD_ODR(GPIOE_PIN4) |              \
                                     PIN_TBD_ODR(GPIOE_PIN5) |              \
                                     PIN_TBD_ODR(GPIOE_PIN6) |              \
                                     PIN_TBD_ODR(GPIOE_PIN7) |              \
                                     PIN_TBD_ODR(GPIOE_PIN8) |              \
                                     PIN_TBD_ODR(GPIOE_PIN9) |              \
                                     PIN_TBD_ODR(GPIOE_PIN10) |             \
                                     PIN_TBD_ODR(GPIOE_PIN11) |             \
                                     PIN_TBD_ODR(GPIOE_PIN12) |             \
                                     PIN_TBD_ODR(GPIOE_PIN13) |             \
                                     PIN_TBD_ODR(GPIOE_PIN14) |             \
                                     PIN_TBD_ODR(GPIOE_PIN15))
#define VAL_GPIOE_AFRL              (PIN_TBD_AF(GPIOE_PIN0) |               \
                                     PIN_TBD_AF(GPIOE_PIN1) |               \
                                     PIN_TBD_AF(GPIOE_PIN2) |               \
                                     PIN_TBD_AF(GPIOE_PIN3) |               \
                                     PIN_TBD_AF(GPIOE_PIN4) |               \
                                     PIN_TBD_AF(GPIOE_PIN5) |               \
                                     PIN_TBD_AF(GPIOE_PIN6) |               \
                                     PIN_TBD_AF(GPIOE_PIN7))
#define VAL_GPIOE_AFRH              (PIN_TBD_AF(GPIOE_PIN8) |               \
                                     PIN_TBD_AF(GPIOE_PIN9) |               \
                                     PIN_TBD_AF(GPIOE_PIN10) |              \
                                     PIN_TBD_AF(GPIOE_PIN11) |              \
                                     PIN_TBD_AF(GPIOE_PIN12) |              \
                                     PIN_TBD_AF(GPIOE_PIN13) |              \
                                     PIN_TBD_AF(GPIOE_PIN14) |              \
                                     PIN_TBD_AF(GPIOE_PIN15))

/*
 * GPIOF setup: all TBD (analog).
 */
#define VAL_GPIOF_MODER             (PIN_TBD_MODE(GPIOF_PIN0) |             \
                                     PIN_TBD_MODE(GPIOF_PIN1) |             \
                                     PIN_TBD_MODE(GPIOF_PIN2) |             \
                                     PIN_TBD_MODE(GPIOF_PIN3) |             \
                                     PIN_TBD_MODE(GPIOF_PIN4) |             \
                                     PIN_TBD_MODE(GPIOF_PIN5) |             \
                                     PIN_TBD_MODE(GPIOF_PIN6) |             \
                                     PIN_TBD_MODE(GPIOF_PIN7) |             \
                                     PIN_TBD_MODE(GPIOF_PIN8) |             \
                                     PIN_TBD_MODE(GPIOF_PIN9) |             \
                                     PIN_TBD_MODE(GPIOF_PIN10) |            \
                                     PIN_TBD_MODE(GPIOF_PIN11) |            \
                                     PIN_TBD_MODE(GPIOF_PIN12) |            \
                                     PIN_TBD_MODE(GPIOF_PIN13) |            \
                                     PIN_TBD_MODE(GPIOF_PIN14) |            \
                                     PIN_TBD_MODE(GPIOF_PIN15))
#define VAL_GPIOF_OTYPER            (PIN_TBD_OTYPE(GPIOF_PIN0) |            \
                                     PIN_TBD_OTYPE(GPIOF_PIN1) |            \
                                     PIN_TBD_OTYPE(GPIOF_PIN2) |            \
                                     PIN_TBD_OTYPE(GPIOF_PIN3) |            \
                                     PIN_TBD_OTYPE(GPIOF_PIN4) |            \
                                     PIN_TBD_OTYPE(GPIOF_PIN5) |            \
                                     PIN_TBD_OTYPE(GPIOF_PIN6) |            \
                                     PIN_TBD_OTYPE(GPIOF_PIN7) |            \
                                     PIN_TBD_OTYPE(GPIOF_PIN8) |            \
                                     PIN_TBD_OTYPE(GPIOF_PIN9) |            \
                                     PIN_TBD_OTYPE(GPIOF_PIN10) |           \
                                     PIN_TBD_OTYPE(GPIOF_PIN11) |           \
                                     PIN_TBD_OTYPE(GPIOF_PIN12) |           \
                                     PIN_TBD_OTYPE(GPIOF_PIN13) |           \
                                     PIN_TBD_OTYPE(GPIOF_PIN14) |           \
                                     PIN_TBD_OTYPE(GPIOF_PIN15))
#define VAL_GPIOF_OSPEEDR           (PIN_TBD_OSPEED(GPIOF_PIN0) |           \
                                     PIN_TBD_OSPEED(GPIOF_PIN1) |           \
                                     PIN_TBD_OSPEED(GPIOF_PIN2) |           \
                                     PIN_TBD_OSPEED(GPIOF_PIN3) |           \
                                     PIN_TBD_OSPEED(GPIOF_PIN4) |           \
                                     PIN_TBD_OSPEED(GPIOF_PIN5) |           \
                                     PIN_TBD_OSPEED(GPIOF_PIN6) |           \
                                     PIN_TBD_OSPEED(GPIOF_PIN7) |           \
                                     PIN_TBD_OSPEED(GPIOF_PIN8) |           \
                                     PIN_TBD_OSPEED(GPIOF_PIN9) |           \
                                     PIN_TBD_OSPEED(GPIOF_PIN10) |          \
                                     PIN_TBD_OSPEED(GPIOF_PIN11) |          \
                                     PIN_TBD_OSPEED(GPIOF_PIN12) |          \
                                     PIN_TBD_OSPEED(GPIOF_PIN13) |          \
                                     PIN_TBD_OSPEED(GPIOF_PIN14) |          \
                                     PIN_TBD_OSPEED(GPIOF_PIN15))
#define VAL_GPIOF_PUPDR             (PIN_TBD_PUPDR(GPIOF_PIN0) |            \
                                     PIN_TBD_PUPDR(GPIOF_PIN1) |            \
                                     PIN_TBD_PUPDR(GPIOF_PIN2) |            \
                                     PIN_TBD_PUPDR(GPIOF_PIN3) |            \
                                     PIN_TBD_PUPDR(GPIOF_PIN4) |            \
                                     PIN_TBD_PUPDR(GPIOF_PIN5) |            \
                                     PIN_TBD_PUPDR(GPIOF_PIN6) |            \
                                     PIN_TBD_PUPDR(GPIOF_PIN7) |            \
                                     PIN_TBD_PUPDR(GPIOF_PIN8) |            \
                                     PIN_TBD_PUPDR(GPIOF_PIN9) |            \
                                     PIN_TBD_PUPDR(GPIOF_PIN10) |           \
                                     PIN_TBD_PUPDR(GPIOF_PIN11) |           \
                                     PIN_TBD_PUPDR(GPIOF_PIN12) |           \
                                     PIN_TBD_PUPDR(GPIOF_PIN13) |           \
                                     PIN_TBD_PUPDR(GPIOF_PIN14) |           \
                                     PIN_TBD_PUPDR(GPIOF_PIN15))
#define VAL_GPIOF_ODR               (PIN_TBD_ODR(GPIOF_PIN0) |              \
                                     PIN_TBD_ODR(GPIOF_PIN1) |              \
                                     PIN_TBD_ODR(GPIOF_PIN2) |              \
                                     PIN_TBD_ODR(GPIOF_PIN3) |              \
                                     PIN_TBD_ODR(GPIOF_PIN4) |              \
                                     PIN_TBD_ODR(GPIOF_PIN5) |              \
                                     PIN_TBD_ODR(GPIOF_PIN6) |              \
                                     PIN_TBD_ODR(GPIOF_PIN7) |              \
                                     PIN_TBD_ODR(GPIOF_PIN8) |              \
                                     PIN_TBD_ODR(GPIOF_PIN9) |              \
                                     PIN_TBD_ODR(GPIOF_PIN10) |             \
                                     PIN_TBD_ODR(GPIOF_PIN11) |             \
                                     PIN_TBD_ODR(GPIOF_PIN12) |             \
                                     PIN_TBD_ODR(GPIOF_PIN13) |             \
                                     PIN_TBD_ODR(GPIOF_PIN14) |             \
                                     PIN_TBD_ODR(GPIOF_PIN15))
#define VAL_GPIOF_AFRL              (PIN_TBD_AF(GPIOF_PIN0) |               \
                                     PIN_TBD_AF(GPIOF_PIN1) |               \
                                     PIN_TBD_AF(GPIOF_PIN2) |               \
                                     PIN_TBD_AF(GPIOF_PIN3) |               \
                                     PIN_TBD_AF(GPIOF_PIN4) |               \
                                     PIN_TBD_AF(GPIOF_PIN5) |               \
                                     PIN_TBD_AF(GPIOF_PIN6) |               \
                                     PIN_TBD_AF(GPIOF_PIN7))
#define VAL_GPIOF_AFRH              (PIN_TBD_AF(GPIOF_PIN8) |               \
                                     PIN_TBD_AF(GPIOF_PIN9) |               \
                                     PIN_TBD_AF(GPIOF_PIN10) |              \
                                     PIN_TBD_AF(GPIOF_PIN11) |              \
                                     PIN_TBD_AF(GPIOF_PIN12) |              \
                                     PIN_TBD_AF(GPIOF_PIN13) |              \
                                     PIN_TBD_AF(GPIOF_PIN14) |              \
                                     PIN_TBD_AF(GPIOF_PIN15))

/*
 * GPIOG setup: all TBD (analog).
 */
#define VAL_GPIOG_MODER             (PIN_TBD_MODE(GPIOG_PIN0) |             \
                                     PIN_TBD_MODE(GPIOG_PIN1) |             \
                                     PIN_TBD_MODE(GPIOG_PIN2) |             \
                                     PIN_TBD_MODE(GPIOG_PIN3) |             \
                                     PIN_TBD_MODE(GPIOG_PIN4) |             \
                                     PIN_TBD_MODE(GPIOG_PIN5) |             \
                                     PIN_TBD_MODE(GPIOG_PIN6) |             \
                                     PIN_TBD_MODE(GPIOG_PIN7) |             \
                                     PIN_TBD_MODE(GPIOG_PIN8) |             \
                                     PIN_TBD_MODE(GPIOG_PIN9) |             \
                                     PIN_TBD_MODE(GPIOG_PIN10) |            \
                                     PIN_TBD_MODE(GPIOG_PIN11) |            \
                                     PIN_TBD_MODE(GPIOG_PIN12) |            \
                                     PIN_TBD_MODE(GPIOG_PIN13) |            \
                                     PIN_TBD_MODE(GPIOG_PIN14) |            \
                                     PIN_TBD_MODE(GPIOG_PIN15))
#define VAL_GPIOG_OTYPER            (PIN_TBD_OTYPE(GPIOG_PIN0) |            \
                                     PIN_TBD_OTYPE(GPIOG_PIN1) |            \
                                     PIN_TBD_OTYPE(GPIOG_PIN2) |            \
                                     PIN_TBD_OTYPE(GPIOG_PIN3) |            \
                                     PIN_TBD_OTYPE(GPIOG_PIN4) |            \
                                     PIN_TBD_OTYPE(GPIOG_PIN5) |            \
                                     PIN_TBD_OTYPE(GPIOG_PIN6) |            \
                                     PIN_TBD_OTYPE(GPIOG_PIN7) |            \
                                     PIN_TBD_OTYPE(GPIOG_PIN8) |            \
                                     PIN_TBD_OTYPE(GPIOG_PIN9) |            \
                                     PIN_TBD_OTYPE(GPIOG_PIN10) |           \
                                     PIN_TBD_OTYPE(GPIOG_PIN11) |           \
                                     PIN_TBD_OTYPE(GPIOG_PIN12) |           \
                                     PIN_TBD_OTYPE(GPIOG_PIN13) |           \
                                     PIN_TBD_OTYPE(GPIOG_PIN14) |           \
                                     PIN_TBD_OTYPE(GPIOG_PIN15))
#define VAL_GPIOG_OSPEEDR           (PIN_TBD_OSPEED(GPIOG_PIN0) |           \
                                     PIN_TBD_OSPEED(GPIOG_PIN1) |           \
                                     PIN_TBD_OSPEED(GPIOG_PIN2) |           \
                                     PIN_TBD_OSPEED(GPIOG_PIN3) |           \
                                     PIN_TBD_OSPEED(GPIOG_PIN4) |           \
                                     PIN_TBD_OSPEED(GPIOG_PIN5) |           \
                                     PIN_TBD_OSPEED(GPIOG_PIN6) |           \
                                     PIN_TBD_OSPEED(GPIOG_PIN7) |           \
                                     PIN_TBD_OSPEED(GPIOG_PIN8) |           \
                                     PIN_TBD_OSPEED(GPIOG_PIN9) |           \
                                     PIN_TBD_OSPEED(GPIOG_PIN10) |          \
                                     PIN_TBD_OSPEED(GPIOG_PIN11) |          \
                                     PIN_TBD_OSPEED(GPIOG_PIN12) |          \
                                     PIN_TBD_OSPEED(GPIOG_PIN13) |          \
                                     PIN_TBD_OSPEED(GPIOG_PIN14) |          \
                                     PIN_TBD_OSPEED(GPIOG_PIN15))
#define VAL_GPIOG_PUPDR             (PIN_TBD_PUPDR(GPIOG_PIN0) |            \
                                     PIN_TBD_PUPDR(GPIOG_PIN1) |            \
                                     PIN_TBD_PUPDR(GPIOG_PIN2) |            \
                                     PIN_TBD_PUPDR(GPIOG_PIN3) |            \
                                     PIN_TBD_PUPDR(GPIOG_PIN4) |            \
                                     PIN_TBD_PUPDR(GPIOG_PIN5) |            \
                                     PIN_TBD_PUPDR(GPIOG_PIN6) |            \
                                     PIN_TBD_PUPDR(GPIOG_PIN7) |            \
                                     PIN_TBD_PUPDR(GPIOG_PIN8) |            \
                                     PIN_TBD_PUPDR(GPIOG_PIN9) |            \
                                     PIN_TBD_PUPDR(GPIOG_PIN10) |           \
                                     PIN_TBD_PUPDR(GPIOG_PIN11) |           \
                                     PIN_TBD_PUPDR(GPIOG_PIN12) |           \
                                     PIN_TBD_PUPDR(GPIOG_PIN13) |           \
                                     PIN_TBD_PUPDR(GPIOG_PIN14) |           \
                                     PIN_TBD_PUPDR(GPIOG_PIN15))
#define VAL_GPIOG_ODR               (PIN_TBD_ODR(GPIOG_PIN0) |              \
                                     PIN_TBD_ODR(GPIOG_PIN1) |              \
                                     PIN_TBD_ODR(GPIOG_PIN2) |              \
                                     PIN_TBD_ODR(GPIOG_PIN3) |              \
                                     PIN_TBD_ODR(GPIOG_PIN4) |              \
                                     PIN_TBD_ODR(GPIOG_PIN5) |              \
                                     PIN_TBD_ODR(GPIOG_PIN6) |              \
                                     PIN_TBD_ODR(GPIOG_PIN7) |              \
                                     PIN_TBD_ODR(GPIOG_PIN8) |              \
                                     PIN_TBD_ODR(GPIOG_PIN9) |              \
                                     PIN_TBD_ODR(GPIOG_PIN10) |             \
                                     PIN_TBD_ODR(GPIOG_PIN11) |             \
                                     PIN_TBD_ODR(GPIOG_PIN12) |             \
                                     PIN_TBD_ODR(GPIOG_PIN13) |             \
                                     PIN_TBD_ODR(GPIOG_PIN14) |             \
                                     PIN_TBD_ODR(GPIOG_PIN15))
#define VAL_GPIOG_AFRL              (PIN_TBD_AF(GPIOG_PIN0) |               \
                                     PIN_TBD_AF(GPIOG_PIN1) |               \
                                     PIN_TBD_AF(GPIOG_PIN2) |               \
                                     PIN_TBD_AF(GPIOG_PIN3) |               \
                                     PIN_TBD_AF(GPIOG_PIN4) |               \
                                     PIN_TBD_AF(GPIOG_PIN5) |               \
                                     PIN_TBD_AF(GPIOG_PIN6) |               \
                                     PIN_TBD_AF(GPIOG_PIN7))
#define VAL_GPIOG_AFRH              (PIN_TBD_AF(GPIOG_PIN8) |               \
                                     PIN_TBD_AF(GPIOG_PIN9) |               \
                                     PIN_TBD_AF(GPIOG_PIN10) |              \
                                     PIN_TBD_AF(GPIOG_PIN11) |              \
                                     PIN_TBD_AF(GPIOG_PIN12) |              \
                                     PIN_TBD_AF(GPIOG_PIN13) |              \
                                     PIN_TBD_AF(GPIOG_PIN14) |              \
                                     PIN_TBD_AF(GPIOG_PIN15))

/*
 * GPIOH setup: only PH0/PH1 available on STM32G474RE (OSC_IN/OUT not used).
 */
#define VAL_GPIOH_MODER             (PIN_TBD_MODE(GPIOH_PIN0) |             \
                                     PIN_TBD_MODE(GPIOH_PIN1))
#define VAL_GPIOH_OTYPER            (PIN_TBD_OTYPE(GPIOH_PIN0) |            \
                                     PIN_TBD_OTYPE(GPIOH_PIN1))
#define VAL_GPIOH_OSPEEDR           (PIN_TBD_OSPEED(GPIOH_PIN0) |           \
                                     PIN_TBD_OSPEED(GPIOH_PIN1))
#define VAL_GPIOH_PUPDR             (PIN_TBD_PUPDR(GPIOH_PIN0) |            \
                                     PIN_TBD_PUPDR(GPIOH_PIN1))
#define VAL_GPIOH_ODR               (PIN_TBD_ODR(GPIOH_PIN0) |              \
                                     PIN_TBD_ODR(GPIOH_PIN1))
#define VAL_GPIOH_AFRL              (PIN_TBD_AF(GPIOH_PIN0) |               \
                                     PIN_TBD_AF(GPIOH_PIN1))
#define VAL_GPIOH_AFRH              0U

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
  void boardInit(void);
#ifdef __cplusplus
}
#endif
#endif /* _FROM_ASM_ */

#endif /* BOARD_H */
