/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/

#ifndef INC_GPT_H_
#define INC_GPT_H_

typedef enum
{
    GPT_CHANNEL_TIM0,
    GPT_CHANNEL_TIM1A,
    GPT_CHANNEL_TIM1B,
    GPT_CHANNEL_TIM2
} Gpt_ChannelType;//enum to hold the channels of the timers of the microcontroller

typedef enum
{
    GPT_INT_SOURCE_TIM0_OV,
    GPT_INT_SOURCE_TIM0_COMP,
    GPT_INT_SOURCE_TIM1_OV,
    GPT_INT_SOURCE_TIM1A_COMP,
    GPT_INT_SOURCE_TIM1B_COMP,
    GPT_INT_SOURCE_TIM2_OV,
    GPT_INT_SOURCE_TIM2_COMP
} Gpt_InterruptSourceType; //enum to hold the interrupt sources of the timers of the microcontroller

void Gpt_Init(void);//function to initialize the timers of the microcontroller
void Gpt_Start(Gpt_ChannelType channel, u16 ticks); //function to start the timer
void Gpt_ResetAndStart(Gpt_ChannelType channel, u16 ticks);//function to reset and start the timer
u16 Gpt_GetTimeElapsed(Gpt_ChannelType channel);//function to get the time elapsed
u16 Gpt_GetTimeRemaining(Gpt_ChannelType channel);//function to get the time remaining
void Gpt_EnableNotification(Gpt_InterruptSourceType channel, void (*callback)(void));//function to enable timer interrupt
void Gpt_DisableNotification(Gpt_InterruptSourceType channel);//function to disable timer interrupt

#endif /* INC_GPT_H_ */