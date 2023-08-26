/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/
#ifndef INC_PWM_H_
#define INC_PWM_H_

typedef enum
{
    PWM_CHANNEL_0,
    PWM_CHANNEL_1A,
    PWM_CHANNEL_1B,
    PWM_CHANNEL_2
} Pwm_ChannelType;//type to hold the channel of the pwm

typedef enum
{
    PWM_PRESCALER_NO_CLOCK,
    PWM_PRESCALER_1,
    PWM_PRESCALER_8,
    PWM_PRESCALER_32,
    PWM_PRESCALER_64,
    PWM_PRESCALER_128,
    PWM_PRESCALER_256,
    PWM_PRESCALER_1024,
    PWM_PRESCALER_EXT_FALLING,
    PWM_PRESCALER_EXT_RISING
} Pwm_PrescalerType;//type to hold the prescaler of the pwm
typedef enum
{
    PWM_OC_DICONNECTED,
    PWM_CLEAR_OC_ON_COMPARE_MATCH,
    PWM_SET_OC_ON_COMPARE_MATCH
} Pwm_SetCompareMatchType;//type to hold the mode of the pwm

void Pwm_Init(Pwm_ChannelType channel);//function to initialize the pwm
void Pwm_SetPrescaler(Pwm_ChannelType channel, Pwm_PrescalerType prescaler);//function to set the prescaler of the pwm
void Pwm_SetCompareValue(Pwm_ChannelType channel, u16 value);//function to set the compare value of the pwm
void Pwm_SetTopValue(u16 value);//function to set the top value of the pwm
void Pwm_SetCompareMatchOutputMode(Pwm_ChannelType channel, Pwm_SetCompareMatchType mode);//function to set the mode of the pwm

#endif /* INC_PWM_H_ */
