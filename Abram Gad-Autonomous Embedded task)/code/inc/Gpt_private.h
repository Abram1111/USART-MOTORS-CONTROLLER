
/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/
#ifndef INC_GPT_PRIVATE_H_
#define INC_GPT_PRIVATE_H_

/******************************************************************
 * GPT Configuration Options
 *****************************************************************/
#define GPT_OFF                                 0
#define GPT_ON                                  1

#define GPT_WAVEFORM_MODE_NORMAL                1
#define GPT_WAVEFORM_MODE_CTC                   2
#define GPT_WAVEFORM_MODE_CTC_ICR1              3

#define GPT_COMPARE_OUTPUT_MODE_DISCONNECTED    1
#define GPT_COMPARE_OUTPUT_MODE_TOG             2
#define GPT_COMPARE_OUTPUT_MODE_CLR             3
#define GPT_COMPARE_OUTPUT_MODE_SET             4

#define GPT_CLK_OFF                             1
#define GPT_CLK_PRESCALER_1                     2
#define GPT_CLK_PRESCALER_8                     3
#define GPT_CLK_PRESCALER_64                    4
#define GPT_CLK_PRESCALER_256                   5
#define GPT_CLK_PRESCALER_1024                  6
#define GPT_CLK_PRESCALER_EXT_FALLING           7
#define GPT_CLK_PRESCALER_EXT_RISING            8


/******************************************************************
 * GPT Registers Bits TIMER 0 
 *****************************************************************/
#define TCCR0_CS00      0
#define TCCR0_CS01      1
#define TCCR0_CS02      2
#define TCCR0_WGM01     3
#define TCCR0_COM00     4
#define TCCR0_COM01     5
#define TCCR0_WGM00     6
#define TCCR0_FOC0      7
/******************************************************************
 * GPT Registers Bits  TIMER 1
 *****************************************************************/
#define TCCR1A_WGM10     0
#define TCCR1A_WGM11     1
#define TCCR1A_FOC1B     2
#define TCCR1A_FOC1A     3
#define TCCR1A_COM1B0    4
#define TCCR1A_COM1B1    5
#define TCCR1A_COM1A0    6
#define TCCR1A_COM1A1    7
/*****************************************************************/
#define TCCR1B_CS10     0
#define TCCR1B_CS11     1
#define TCCR1B_CS12     2
#define TCCR1B_WGM12    3
#define TCCR1B_WGM13    4
#define TCCR1B_ICES1    6
#define TCCR1B_ICNC1    7
/******************************************************************
 * GPT Registers Bits  TIMER 2
 *****************************************************************/
#define TCCR2_CS20      0
#define TCCR2_CS21      1
#define TCCR2_CS22      2
#define TCCR2_WGM21     3
#define TCCR2_COM20     4
#define TCCR2_COM21     5
#define TCCR2_WGM20     6
#define TCCR2_FOC2      7
/******************************************************************
 * GPT Registers Bits  Interrupt 
 *****************************************************************/
#define TIMSK_OCIE2     7
#define TIMSK_TOIE2     6
#define TIMSK_TICIE1    5
#define TIMSK_OCIE1A    4
#define TIMSK_OCIE1B    3
#define TIMSK_TOIE1     2
#define TIMSK_OCIE0     1
#define TIMSK_TOIE0     0



#define TIFR_TOV0       0
#define TIFR_OCF0       1
#define TIFR_TOV1       2
#define TIFR_OCF1B      3
#define TIFR_OCF1A      4
#define TIFR_ICF1       5
#define TIFR_TOV2       6
#define TIFR_OCF2       7


#endif /* INC_GPT_PRIVATE_H_ */