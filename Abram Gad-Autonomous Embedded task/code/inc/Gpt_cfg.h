/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/

#ifndef INC_GPT_CFG_H_
#define INC_GPT_CFG_H_

#include <Gpt_private.h>

/******************************************************************
 * OPTIONS
 *****************************************************************/

/*
---> Options For WAVEFORM_MODE:
        GPT_WAVEFORM_MODE_NORMAL
        GPT_WAVEFORM_MODE_CTC
        GPT_WAVEFORM_MODE_CTC_ICR1 (for timer 1 only)
---> Options For COMPARE_OUTPUT_MODE:
        GPT_COMPARE_OUTPUT_MODE_DISCONNECTED
        GPT_COMPARE_OUTPUT_MODE_TOG
        GPT_COMPARE_OUTPUT_MODE_CLR
        GPT_COMPARE_OUTPUT_MODE_SET
---> Options For CLK:
        GPT_CLK_OFF
        GPT_CLK_PRESCALER_1
        GPT_CLK_PRESCALER_8
        GPT_CLK_PRESCALER_64
        GPT_CLK_PRESCALER_256
        GPT_CLK_PRESCALER_1024
        GPT_CLK_PRESCALER_EXT_FALLING
        GPT_CLK_PRESCALER_EXT_RISING
*/


/******************************************************************
 * Configuration
 *****************************************************************/

#define GPT_TIM0_STATUS GPT_ON
#if GPT_TIM0_STATUS == GPT_ON           /* Timer 0 Configurations */
#define GPT_TIM0_WAVEFORM_MODE          GPT_WAVEFORM_MODE_CTC
#define GPT_TIM0_COMPARE_OUTPUT_MODE    GPT_COMPARE_OUTPUT_MODE_DISCONNECTED
#define GPT_TIM0_CLK                    GPT_CLK_PRESCALER_8
#endif

#define GPT_TIM1_STATUS GPT_OFF
#if GPT_TIM1_STATUS == GPT_ON           /* Timer 1 Configurations */
#define GPT_TIM1_WAVEFORM_MODE          GPT_WAVEFORM_MODE_NORMAL
#define GPT_TIM1A_COMPARE_OUTPUT_MODE   GPT_COMPARE_OUTPUT_MODE_DISCONNECTED
#define GPT_TIM1B_COMPARE_OUTPUT_MODE   GPT_COMPARE_OUTPUT_MODE_DISCONNECTED
#define GPT_TIM1_CLK                    GPT_CLK_PRESCALER_8
#endif

#define GPT_TIM2_STATUS GPT_OFF
#if GPT_TIM2_STATUS == GPT_ON           /* Timer 2 Configurations */
#define GPT_TIM2_WAVEFORM_MODE          GPT_WAVEFORM_MODE_CTC
#define GPT_TIM2_COMPARE_OUTPUT_MODE    GPT_COMPARE_OUTPUT_MODE_DISCONNECTED
#define GPT_TIM2_CLK                    GPT_CLK_PRESCALER_8
#endif

#endif /* INC_GPT_CFG_H_ */