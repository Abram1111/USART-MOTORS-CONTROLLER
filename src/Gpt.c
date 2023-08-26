/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/


#include <std_types.h>
#include <Macros.h>
#include <Registers.h>
#include <Interrupts.h>
#include <Gpt_private.h>
#include <Gpt_cfg.h>
#include <Gpt.h>

/******************************************************************
 * Timer ISR
 *****************************************************************/
//pointer to function to hold the address of the function that will be called when the interrupt occurs
void (*Gpt_CallbackTim0_Compare)(void);
void (*Gpt_CallbackTim0_Overflow)(void);
void (*Gpt_CallbackTim1A_Compare)(void);
void (*Gpt_CallbackTim1B_Compare)(void);
void (*Gpt_CallbackTim1_Overflow)(void);
void (*Gpt_CallbackTim2_Compare)(void);
void (*Gpt_CallbackTim2_Overflow)(void);
/******************************************************************
 * ISR Functions
 *****************************************************************/

ISR(VECTOR_TIM0_COMP)
{
    Gpt_CallbackTim0_Compare();
}
ISR(VECTOR_TIM0_OV)
{
    Gpt_CallbackTim0_Overflow();
}
ISR(VECTOR_TIM1A_COMP)
{
    Gpt_CallbackTim1A_Compare();
}
ISR(VECTOR_TIM1B_COMP)
{
    
    Gpt_CallbackTim1B_Compare();
}
ISR(VECTOR_TIM1_OV)
{
    
    Gpt_CallbackTim1_Overflow();
}
ISR(VECTOR_TIM2_COMP)
{
    
    Gpt_CallbackTim2_Compare();
}
ISR(VECTOR_TIM2_OV)
{
    
    Gpt_CallbackTim2_Overflow();
}

void Gpt_Init(void)
{

/******************************************************************
 * Timer 0 Init
 *****************************************************************/
#if GPT_TIM0_STATUS == GPT_ON

/* Waveform Generation Mode */
#if GPT_TIM0_WAVEFORM_MODE == GPT_WAVEFORM_MODE_NORMAL
    CLR_BIT(TCCR0, TCCR0_WGM00);
    CLR_BIT(TCCR0, TCCR0_WGM01);
#elif GPT_TIM0_WAVEFORM_MODE == GPT_WAVEFORM_MODE_CTC
    CLR_BIT(TCCR0, TCCR0_WGM00);
    SET_BIT(TCCR0, TCCR0_WGM01);
#else
#error "Invalid WAVEFORM_MODE For TIM0"
#endif

/* Compare Match Output Mode */
#if GPT_TIM0_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_DISCONNECTED
    CLR_BIT(TCCR0, TCCR0_COM00);
    CLR_BIT(TCCR0, TCCR0_COM01);
#elif GPT_TIM0_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_TOG
   
    SET_BIT(TCCR0, TCCR0_COM00);
    CLR_BIT(TCCR0, TCCR0_COM01);
#elif GPT_TIM0_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_CLR
    
    CLR_BIT(TCCR0, TCCR0_COM00);
    SET_BIT(TCCR0, TCCR0_COM01);
#elif GPT_TIM0_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_SET
    
    SET_BIT(TCCR0, TCCR0_COM00);
    SET_BIT(TCCR0, TCCR0_COM01);
#else
#error "Invalid COMPARE_OUTPUT_MODE For TIM0"
#endif

/* Clock Select */
#if GPT_TIM0_CLK == GPT_CLK_OFF
    
    CLR_BIT(TCCR0, TCCR0_CS00);
    CLR_BIT(TCCR0, TCCR0_CS01);
    CLR_BIT(TCCR0, TCCR0_CS02);
#elif GPT_TIM0_CLK == GPT_CLK_PRESCALER_1
    
    SET_BIT(TCCR0, TCCR0_CS00);
    CLR_BIT(TCCR0, TCCR0_CS01);
    CLR_BIT(TCCR0, TCCR0_CS02);
#elif GPT_TIM0_CLK == GPT_CLK_PRESCALER_8
    CLR_BIT(TCCR0, TCCR0_CS00);
    SET_BIT(TCCR0, TCCR0_CS01);
    CLR_BIT(TCCR0, TCCR0_CS02);
#elif GPT_TIM0_CLK == GPT_CLK_PRESCALER_64
    
    SET_BIT(TCCR0, TCCR0_CS00);
    SET_BIT(TCCR0, TCCR0_CS01);
    CLR_BIT(TCCR0, TCCR0_CS02);
#elif GPT_TIM0_CLK == GPT_CLK_PRESCALER_256
    
    CLR_BIT(TCCR0, TCCR0_CS00);
    CLR_BIT(TCCR0, TCCR0_CS01);
    SET_BIT(TCCR0, TCCR0_CS02);
#elif GPT_TIM0_CLK == GPT_CLK_PRESCALER_1024
    
    SET_BIT(TCCR0, TCCR0_CS00);
    CLR_BIT(TCCR0, TCCR0_CS01);
    SET_BIT(TCCR0, TCCR0_CS02);
#elif GPT_TIM0_CLK == GPT_CLK_PRESCALER_EXT_FALLING
    
    CLR_BIT(TCCR0, TCCR0_CS00);
    SET_BIT(TCCR0, TCCR0_CS01);
    SET_BIT(TCCR0, TCCR0_CS02);
#elif GPT_TIM0_CLK == GPT_CLK_PRESCALER_EXT_RISING
    
    SET_BIT(TCCR0, TCCR0_CS00);
    SET_BIT(TCCR0, TCCR0_CS01);
    SET_BIT(TCCR0, TCCR0_CS02);
#else
#error "Invalid Configuration for CLK in TIM0"
#endif

#endif

/******************************************************************
 * Timer 1 Init
 *****************************************************************/
#if GPT_TIM1_STATUS == GPT_ON

/* Waveform Generation Mode */
#if GPT_TIM1_WAVEFORM_MODE == GPT_WAVEFORM_MODE_NORMAL
    
    CLR_BIT(TCCR1A, TCCR1A_WGM10);
    CLR_BIT(TCCR1A, TCCR1A_WGM11);
    CLR_BIT(TCCR1B, TCCR1B_WGM12);
    CLR_BIT(TCCR1B, TCCR1B_WGM13);
#elif GPT_TIM1_WAVEFORM_MODE == GPT_WAVEFORM_MODE_CTC
    
    CLR_BIT(TCCR1A, TCCR1A_WGM10);
    CLR_BIT(TCCR1A, TCCR1A_WGM11);
    SET_BIT(TCCR1B, TCCR1B_WGM12);
    CLR_BIT(TCCR1B, TCCR1B_WGM13);
#elif GPT_TIM1_WAVEFORM_MODE == GPT_WAVEFORM_MODE_CTC_ICR1
    CLR_BIT(TCCR1A, TCCR1A_WGM10);
    CLR_BIT(TCCR1A, TCCR1A_WGM11);
    SET_BIT(TCCR1B, TCCR1B_WGM12);
    SET_BIT(TCCR1B, TCCR1B_WGM13);
#else
#error "Invalid WAVEFORM_MODE For TIM1"
#endif

/* Compare Match Output Mode For Channel A */
#if GPT_TIM1A_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_DISCONNECTED
    
    CLR_BIT(TCCR1A, TCCR1A_COM1A0);
    CLR_BIT(TCCR1A, TCCR1A_COM1A1);
#elif GPT_TIM1A_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_TOG
    
    SET_BIT(TCCR1A, TCCR1A_COM1A0);
    CLR_BIT(TCCR1A, TCCR1A_COM1A1);
#elif GPT_TIM1A_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_CLR
    
    CLR_BIT(TCCR1A, TCCR1A_COM1A0);
    SET_BIT(TCCR1A, TCCR1A_COM1A1);
#elif GPT_TIM1A_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_SET
    
    SET_BIT(TCCR1A, TCCR1A_COM1A0);
    SET_BIT(TCCR1A, TCCR1A_COM1A1);
#else
#error "Invalid COMPARE_OUTPUT_MODE For TIM1A"
#endif

/* Compare Match Output Mode For Channel B */
#if GPT_TIM1B_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_DISCONNECTED
    
    CLR_BIT(TCCR1A, TCCR1A_COM1B0);
    CLR_BIT(TCCR1A, TCCR1A_COM1B1);
#elif GPT_TIM1B_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_TOG
    
    SET_BIT(TCCR1A, TCCR1A_COM1B0);
    CLR_BIT(TCCR1A, TCCR1A_COM1B1);
#elif GPT_TIM1B_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_CLR
    
    CLR_BIT(TCCR1A, TCCR1A_COM1B0);
    SET_BIT(TCCR1A, TCCR1A_COM1B1);
#elif GPT_TIM1B_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_SET
    
    SET_BIT(TCCR1A, TCCR1A_COM1B0);
    SET_BIT(TCCR1A, TCCR1A_COM1B1);
#else
#error "Invalid COMPARE_OUTPUT_MODE For TIM1B"
#endif

/* Clock Select */
#if GPT_TIM1_CLK == GPT_CLK_OFF
    
    CLR_BIT(TCCR1B, TCCR1B_CS10);
    CLR_BIT(TCCR1B, TCCR1B_CS11);
    CLR_BIT(TCCR1B, TCCR1B_CS12);
#elif GPT_TIM1_CLK == GPT_CLK_PRESCALER_1
    
    SET_BIT(TCCR1B, TCCR1B_CS10);
    CLR_BIT(TCCR1B, TCCR1B_CS11);
    CLR_BIT(TCCR1B, TCCR1B_CS12);
#elif GPT_TIM1_CLK == GPT_CLK_PRESCALER_8
    
    CLR_BIT(TCCR1B, TCCR1B_CS10);
    SET_BIT(TCCR1B, TCCR1B_CS11);
    CLR_BIT(TCCR1B, TCCR1B_CS12);
#elif GPT_TIM1_CLK == GPT_CLK_PRESCALER_64
    
    SET_BIT(TCCR1B, TCCR1B_CS10);
    SET_BIT(TCCR1B, TCCR1B_CS11);
    CLR_BIT(TCCR1B, TCCR1B_CS12);
#elif GPT_TIM1_CLK == GPT_CLK_PRESCALER_256
    
    CLR_BIT(TCCR1B, TCCR1B_CS10);
    CLR_BIT(TCCR1B, TCCR1B_CS11);
    SET_BIT(TCCR1B, TCCR1B_CS12);
#elif GPT_TIM1_CLK == GPT_CLK_PRESCALER_1024
    
    SET_BIT(TCCR1B, TCCR1B_CS10);
    CLR_BIT(TCCR1B, TCCR1B_CS11);
    SET_BIT(TCCR1B, TCCR1B_CS12);
#elif GPT_TIM1_CLK == GPT_CLK_PRESCALER_EXT_FALLING
    
    CLR_BIT(TCCR1B, TCCR1B_CS10);
    SET_BIT(TCCR1B, TCCR1B_CS11);
    SET_BIT(TCCR1B, TCCR1B_CS12);
#elif GPT_TIM1_CLK == GPT_CLK_PRESCALER_EXT_RISING
    
    SET_BIT(TCCR1B, TCCR1B_CS10);
    SET_BIT(TCCR1B, TCCR1B_CS11);
    SET_BIT(TCCR1B, TCCR1B_CS12);
#else
#error "Invalid Configuration for CLK in TIM1"
#endif

#endif

/******************************************************************
 * Timer 2 Init
 *****************************************************************/
#if GPT_TIM2_STATUS == GPT_ON

/* Waveform Generation Mode */
#if GPT_TIM2_WAVEFORM_MODE == GPT_WAVEFORM_MODE_NORMAL
    
    CLR_BIT(TCCR2, TCCR2_WGM20);
    CLR_BIT(TCCR2, TCCR2_WGM21);

#elif GPT_TIM2_WAVEFORM_MODE == GPT_WAVEFORM_MODE_CTC
    
    CLR_BIT(TCCR2, TCCR2_WGM20);
    SET_BIT(TCCR2, TCCR2_WGM21);
#else
#error "Invalid WAVEFORM_MODE For TIM2"
#endif

/* Compare Match Output Mode */
#if GPT_TIM2_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_DISCONNECTED
    
    CLR_BIT(TCCR2, TCCR2_COM20);
    CLR_BIT(TCCR2, TCCR2_COM21);
#elif GPT_TIM2_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_TOG
    
    SET_BIT(TCCR2, TCCR2_COM20);
    CLR_BIT(TCCR2, TCCR2_COM21);
#elif GPT_TIM2_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_CLR
    
    CLR_BIT(TCCR2, TCCR2_COM20);
    SET_BIT(TCCR2, TCCR2_COM21);
#elif GPT_TIM2_COMPARE_OUTPUT_MODE == GPT_COMPARE_OUTPUT_MODE_SET
    
    SET_BIT(TCCR2, TCCR2_COM20);
    SET_BIT(TCCR2, TCCR2_COM21);
#else
#error "Invalid COMPARE_OUTPUT_MODE For TIM2"
#endif

/* Clock Select */
#if GPT_TIM2_CLK == GPT_CLK_OFF
    
    CLR_BIT(TCCR2, TCCR2_CS20);
    CLR_BIT(TCCR2, TCCR2_CS21);
    CLR_BIT(TCCR2, TCCR2_CS22);

#elif GPT_TIM2_CLK == GPT_CLK_PRESCALER_1
    
    SET_BIT(TCCR2, TCCR2_CS20);
    CLR_BIT(TCCR2, TCCR2_CS21);
    CLR_BIT(TCCR2, TCCR2_CS22);
#elif GPT_TIM2_CLK == GPT_CLK_PRESCALER_8
    
    CLR_BIT(TCCR2, TCCR2_CS20);
    SET_BIT(TCCR2, TCCR2_CS21);
    CLR_BIT(TCCR2, TCCR2_CS22);
#elif GPT_TIM2_CLK == GPT_CLK_PRESCALER_32
    
    SET_BIT(TCCR2, TCCR2_CS20);
    SET_BIT(TCCR2, TCCR2_CS21);
    CLR_BIT(TCCR2, TCCR2_CS22);
#elif GPT_TIM2_CLK == GPT_CLK_PRESCALER_64
    
    CLR_BIT(TCCR2, TCCR2_CS20);
    CLR_BIT(TCCR2, TCCR2_CS21);
    SET_BIT(TCCR2, TCCR2_CS22);
#elif GPT_TIM2_CLK == GPT_CLK_PRESCALER_128
    
    SET_BIT(TCCR2, TCCR2_CS20);
    CLR_BIT(TCCR2, TCCR2_CS21);
    SET_BIT(TCCR2, TCCR2_CS22);
#elif GPT_TIM2_CLK == GPT_CLK_PRESCALER_256
    
    CLR_BIT(TCCR2, TCCR2_CS20);
    SET_BIT(TCCR2, TCCR2_CS21);
    SET_BIT(TCCR2, TCCR2_CS22);
#elif GPT_TIM2_CLK == GPT_CLK_PRESCALER_1024
    
    SET_BIT(TCCR2, TCCR2_CS20);
    SET_BIT(TCCR2, TCCR2_CS21);
    SET_BIT(TCCR2, TCCR2_CS22);
#else
#error "Invalid Configuration for CLK in TIM2"
#endif

#endif
}

void Gpt_Start(Gpt_ChannelType channel, u16 ticks)
{
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        OCR0 = ticks;
        break;
    case GPT_CHANNEL_TIM1A:
        
        OCR1A = ticks;
        break;
    case GPT_CHANNEL_TIM1B:
        
        OCR1B = ticks;
        break;
    case GPT_CHANNEL_TIM2:
        
        OCR2 = ticks;
        break;
    default:
        break;
    }
}

void Gpt_ResetAndStart(Gpt_ChannelType channel, u16 ticks)
{
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        OCR0 = ticks;
        TCNT0 = 0;
        break;
    case GPT_CHANNEL_TIM1A:
        
        OCR1A = ticks;
        TCNT1 = 0;
        break;
    case GPT_CHANNEL_TIM1B:
        
        OCR1B = ticks;
        TCNT1 = 0;
        break;
    case GPT_CHANNEL_TIM2:
        
        OCR2 = ticks;
        TCNT2 = 0;
        break;
    default:
        break;
    }
}

u16 Gpt_GetTimeElapsed(Gpt_ChannelType channel)
{
    u16 result = 0;
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
        result = TCNT0;
        break;

    case GPT_CHANNEL_TIM1A:
    case GPT_CHANNEL_TIM1B:
        
        result = TCNT1;
        break;

    case GPT_CHANNEL_TIM2:
        
        result = TCNT2;
        break;

    default:
        break;
    }
    return result;
}

u16 Gpt_GetTimeRemaining(Gpt_ChannelType channel)
{
    u16 result = 0;
    switch (channel)
    {
    case GPT_CHANNEL_TIM0:
#if GPT_TIM0_WAVEFORM_MODE == GPT_WAVEFORM_MODE_CTC
        result = OCR0 - TCNT0;
#elif GPT_TIM0_WAVEFORM_MODE == GPT_WAVEFORM_MODE_NORMAL
        result = 0xFF - TCNT0;
#endif
        break;

    case GPT_CHANNEL_TIM1A:
        
#if GPT_TIM1_WAVEFORM_MODE == GPT_WAVEFORM_MODE_CTC
        result = OCR1A - TCNT1;
#elif GPT_TIM1_WAVEFORM_MODE == GPT_WAVEFORM_MODE_CTC_ICR1
        result = ICR1 - TCNT1;
#elif GPT_TIM1_WAVEFORM_MODE == GPT_WAVEFORM_MODE_NORMAL
        result = 0xFFFF - TCNT1;
#endif
        break;

    case GPT_CHANNEL_TIM1B:
        
#if GPT_TIM1_WAVEFORM_MODE == GPT_WAVEFORM_MODE_CTC
        result = OCR1B - TCNT1;
#elif GPT_TIM1_WAVEFORM_MODE == GPT_WAVEFORM_MODE_CTC_ICR1
        result = ICR1 - TCNT1;
#elif GPT_TIM1_WAVEFORM_MODE == GPT_WAVEFORM_MODE_NORMAL
        result = 0xFFFF - TCNT1;
#endif
        break;

    case GPT_CHANNEL_TIM2:
        
#if GPT_TIM2_WAVEFORM_MODE == GPT_WAVEFORM_MODE_CTC
        result = OCR2 - TCNT2;
#elif GPT_TIM2_WAVEFORM_MODE == GPT_WAVEFORM_MODE_NORMAL
        result = 0xFF - TCNT2;
#endif
        break;

    default:
        break;
    }
    return result;
}

void Gpt_EnableNotification(Gpt_InterruptSourceType channel, void (*callback)(void))
{
    switch (channel)
    {
    case GPT_INT_SOURCE_TIM0_OV:
        Gpt_CallbackTim0_Overflow = callback;
        SET_BIT(TIMSK, TIMSK_TOIE0);
        break;
    case GPT_INT_SOURCE_TIM0_COMP:
        Gpt_CallbackTim0_Compare = callback;
        SET_BIT(TIMSK, TIMSK_OCIE0);
        break;
    case GPT_INT_SOURCE_TIM1_OV:
        
        Gpt_CallbackTim1_Overflow = callback;
        SET_BIT(TIMSK, TIMSK_TOIE1);
        break;
    case GPT_INT_SOURCE_TIM1A_COMP:
        
        Gpt_CallbackTim1A_Compare = callback;
        SET_BIT(TIMSK, TIMSK_OCIE1A);
        break;
    case GPT_INT_SOURCE_TIM1B_COMP:
        
        Gpt_CallbackTim1B_Compare = callback;
        SET_BIT(TIMSK, TIMSK_OCIE1B);
        break;
    case GPT_INT_SOURCE_TIM2_OV:
        
        Gpt_CallbackTim2_Overflow = callback;
        SET_BIT(TIMSK, TIMSK_TOIE2);
        break;
    case GPT_INT_SOURCE_TIM2_COMP:
        
        Gpt_CallbackTim2_Compare = callback;
        SET_BIT(TIMSK, TIMSK_OCIE2);
        break;
    }
}

void Gpt_DisableNotification(Gpt_InterruptSourceType channel)
{
    switch (channel)
    {
    case GPT_INT_SOURCE_TIM0_OV:
        CLR_BIT(TIMSK, TIMSK_TOIE0);
        break;
    case GPT_INT_SOURCE_TIM0_COMP:
        CLR_BIT(TIMSK, TIMSK_OCIE0);
        break;
    case GPT_INT_SOURCE_TIM1_OV:
        
        CLR_BIT(TIMSK, TIMSK_TOIE1);
        break;
    case GPT_INT_SOURCE_TIM1A_COMP:
        
        CLR_BIT(TIMSK, TIMSK_OCIE1A);
        break;
    case GPT_INT_SOURCE_TIM1B_COMP:
        
        CLR_BIT(TIMSK, TIMSK_OCIE1B);
        break;
    case GPT_INT_SOURCE_TIM2_OV:
        
        CLR_BIT(TIMSK, TIMSK_TOIE2);
        break;
    case GPT_INT_SOURCE_TIM2_COMP:
        
        CLR_BIT(TIMSK, TIMSK_OCIE2);
        break;
    }
}