/*
 * snippets.c
 *
 *  Created on: 24.11.2015
 *      Author: ziemannt
 */

    timing.osc_pretrigger_cycles = osc_pretrigger_time * TIMER_CLOCK;
    timing.first_pulse_cycles = running_test.first_pulse_length * TIMER_CLOCK;
    timing.pulse_separation_cycles = pulse_separation * TIMER_CLOCK;
    timing.second_pulse_cycles = second_pulse_length * TIMER_CLOCK;
    timing.HV_switch_deadtime_cycles = HV_switch_deadtime * TIMER_CLOCK;
    timing.LV_switch_deadtime_cycles = LV_switch_deadtime * TIMER_CLOCK;

// alternate test sequence timing:

    //gptStart(&GPTD4, &gpt4cfg);             // start timer
    //test_starttime = chVTGetSystemTime();

    //    chSysLock();
    //    palSetPad(GPIOC, GPIOC_Trigger_TX);                         // trigger on
    //    gptPolledDelay(&GPTD4, timing.osc_pretrigger_cycles-1);     // pretrigger in timer cycles
    //    palSetPad(GPIOC, GPIOC_DUT_TX);                             // enable DUT switch @ 1.4656us
    //    gptPolledDelay(&GPTD4, timing.LV_switch_deadtime_cycles-1); // deadtime delay in timer cycles 2.4867us
    //    palSetPad(GPIOC, GPIOC_LV_TX);                              // enable LV switch @ 3.9523 us
    //    gptPolledDelay(&GPTD4, timing.first_pulse_cycles-1);        // FIRST PULSE
    //    palClearPad(GPIOC, GPIOC_LV_TX);                            // deactivate LV switch 903.55us
    //    gptPolledDelay(&GPTD4, timing.LV_switch_deadtime_cycles-1); // deadtime delay in timer cycles 2.507us
    //    palClearPad(GPIOC, GPIOC_DUT_TX);                           // deactivate DUT switch 906.057
    //    gptPolledDelay(&GPTD4, timing.HV_switch_deadtime_cycles-1); // deadtime delay in timer cycles 1.683us
    //    palSetPad(GPIOC, GPIOC_HV_TX);                              // activate HV switch 907.74
    //    gptPolledDelay(&GPTD4, timing.pulse_separation_cycles-timing.HV_switch_deadtime_cycles*2-1);     // pulse separation minus deadtime delay in timer cycles
    //    palClearPad(GPIOC, GPIOC_HV_TX);                            // deactivate HV switch 919.056
    //    gptPolledDelay(&GPTD4, timing.HV_switch_deadtime_cycles-1); // deadtime delay in timer cycles
    //    palSetPad(GPIOC, GPIOC_DUT_TX);                             // enable DUT switch 920.748
    //    gptPolledDelay(&GPTD4, timing.second_pulse_cycles-1);       // SECOND PULSE
    //    palClearPad(GPIOC, GPIOC_DUT_TX);                           // disable DUT switch 932.227
    //    gptPolledDelay(&GPTD4, timing.HV_switch_deadtime_cycles-1); // deadtime delay in timer cycles
    //    palSetPad(GPIOC, GPIOC_HV_TX);                              // activate HV switch 933.8826
    //    chSysUnlock();
    //    chThdSleep(S2ST(discharge_time));                           // discharge time
    //    palClearPad(GPIOC, GPIOC_HV_TX);                            // deactivate HV switch 1.000965s
    //    gptPolledDelay(&GPTD4, timing.osc_pretrigger_cycles-1);     // pretrigger in timer cycles
    //    palClearPad(GPIOC, GPIOC_Trigger_TX);                       // trigger off*/

    //
    //
    //// GPT8 callback.
    //static void gpt8cb(GPTDriver *gptp)
    //{
    //  (void)gptp;
    //
    //  timer_4_counter = TIM4->CNT;      // TODO is CNT updated at this time or not? CNT or CNT+1?
    //
    //  if (timing.trigger_off/65536 == timer_4_counter)  // if match should occur in this timer period
    //  {
    //    TIM8->CCER |= TIM_CCER_CC1E;
    //  }
    //
    //  if (timing.LV_on/65536 == timer_4_counter)  // if match should occur in this timer period
    //  {
    //    TIM8->CCER |= TIM_CCER_CC2E;
    //  }
    //  else if (timing.LV_off/65536 == timer_4_counter)  // if match should occur in this timer period
    //  {
    //    TIM8->CCER |= TIM_CCER_CC2E;
    //  }
    //
    //  if (timing.HV_first_on/65536 == timer_4_counter)  // if match should occur in this timer period
    //  {
    //    TIM8->CCER |= TIM_CCER_CC3E;
    //  }
    //  else if (timing.HV_first_off/65536 == timer_4_counter)  // if match should occur in this timer period
    //  {
    //    TIM8->CCER |= TIM_CCER_CC3E;
    //  }
    //  else if (timing.HV_second_on/65536 == timer_4_counter)  // if match should occur in this timer period
    //  {
    //    TIM8->CCER |= TIM_CCER_CC3E;
    //  }
    //  else if (timing.HV_second_off/65536 == timer_4_counter)  // if match should occur in this timer period
    //  {
    //    TIM8->CCER |= TIM_CCER_CC3E;
    //  }
    //

    //
    //}
    //
    //// GPT8 configuration.
    //static const GPTConfig gpt8cfg =
    //{
    // TIMER_CLOCK,
    // &gpt8cb          // Timer callback.
    //};
    //
    //
    //// start timer 4
    //void timer_4_start(void)
    //{
    //  RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;                       // enable timer clock
    //  TIM4->SMCR |= (TIM_SMCR_TS_0
    //      | TIM_SMCR_TS_1
    //      | TIM_SMCR_SMS_0
    //      | TIM_SMCR_SMS_1
    //      | TIM_SMCR_SMS_2);                           // enable slave mode from trigger channel 3
    //  TIM4->CR1 |= TIM_CR1_CEN | TIM_CR1_OPM;                   // start timer in one pulse mode
    //}
    //
    //
