/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/

#include <std_types.h>
#include <Macros.h>
#include <Registers.h>
#include <Dio.h>
#include <Gpt_private.h>
#include <Pwm.h>
void Pwm_Init(Pwm_ChannelType channel)
{
    switch (channel)
    {
    case PWM_CHANNEL_0:
        /* Waveform Generation Mode: Fast PWM */
        SET_BIT(TCCR0, TCCR0_WGM00);
        SET_BIT(TCCR0, TCCR0_WGM01);
        /* Clock Select: No Prescaler */
        SET_BIT(TCCR0, TCCR0_CS00);
        CLR_BIT(TCCR0, TCCR0_CS01);
        CLR_BIT(TCCR0, TCCR0_CS02);
        /* Set OC0 Pin as Output */
        Dio_SetPinMode(DIO_PORTB, DIO_PIN3, DIO_PIN_OUTPUT);
        /* Compare Match Output Mode:
                Clear OC0 on compare match, set OC0 at TOP */
        CLR_BIT(TCCR0, TCCR0_COM00);
        SET_BIT(TCCR0, TCCR0_COM01);
        break;

    case PWM_CHANNEL_1A:
    case PWM_CHANNEL_1B:
        /* Waveform Generation Mode: Fast PWM, TOP=ICR1 */
        CLR_BIT(TCCR1A, TCCR1A_WGM10);
        SET_BIT(TCCR1A, TCCR1A_WGM11);
        SET_BIT(TCCR1B, TCCR1B_WGM12);
        SET_BIT(TCCR1B, TCCR1B_WGM13);
        /* Clock Select: No Prescaler */
        SET_BIT(TCCR1B, TCCR1B_CS10);
        CLR_BIT(TCCR1B, TCCR1B_CS11);
        CLR_BIT(TCCR1B, TCCR1B_CS12);
        if (channel == PWM_CHANNEL_1A)
        {
            /* Compare Match Output Mode:
                    Clear OC1A on compare match, set OC1A at TOP */
            CLR_BIT(TCCR1A, TCCR1A_COM1A0);
            SET_BIT(TCCR1A, TCCR1A_COM1A1);
            /* Set OC1A Pin as Output */
            Dio_SetPinMode(DIO_PORTD, DIO_PIN5, DIO_PIN_OUTPUT);
        }
        else if (channel == PWM_CHANNEL_1B)
        {
            /* Compare Match Output Mode:
                    Clear OC1B on compare match, set OC1B at TOP */
            CLR_BIT(TCCR1A, TCCR1A_COM1B0);
            SET_BIT(TCCR1A, TCCR1A_COM1B1);
            /* Set OC1B Pin as Output */
            Dio_SetPinMode(DIO_PORTD, DIO_PIN4, DIO_PIN_OUTPUT);
        }
        break;
    case PWM_CHANNEL_2:
        
        /* Waveform Generation Mode: Fast PWM */
        SET_BIT(TCCR2, TCCR2_WGM20);
        SET_BIT(TCCR2, TCCR2_WGM21);
        /* Clock Select: No Prescaler */
        SET_BIT(TCCR2, TCCR2_CS20);
        CLR_BIT(TCCR2, TCCR2_CS21);
        CLR_BIT(TCCR2, TCCR2_CS22);
        /* Set OC2 Pin as Output */
        Dio_SetPinMode(DIO_PORTD, DIO_PIN7, DIO_PIN_OUTPUT);
        /* Compare Match Output Mode:
                Clear OC2 on compare match, set OC2 at TOP */
        CLR_BIT(TCCR2, TCCR2_COM20);
        SET_BIT(TCCR2, TCCR2_COM21);
        break;
    default:
        break;
    }
}

void Pwm_SetPrescaler(Pwm_ChannelType channel, Pwm_PrescalerType prescaler)
{
    switch (channel)
    {
    case PWM_CHANNEL_0:
        switch (prescaler)
        {
        case PWM_PRESCALER_NO_CLOCK:
            CLR_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        case PWM_PRESCALER_8:
            CLR_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        case PWM_PRESCALER_64:
            
            SET_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        case PWM_PRESCALER_256:
            
            CLR_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;
        case PWM_PRESCALER_1024:
            
            SET_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;
        case PWM_PRESCALER_EXT_FALLING:
            
            CLR_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;
        case PWM_PRESCALER_EXT_RISING:
            
            SET_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;
        default:
            break;
        }
        break;

    case PWM_CHANNEL_1A:
    case PWM_CHANNEL_1B:
        switch (prescaler)
        {
        case PWM_PRESCALER_NO_CLOCK:
            CLR_BIT(TCCR1B, TCCR1B_CS10);
            CLR_BIT(TCCR1B, TCCR1B_CS11);
            CLR_BIT(TCCR1B, TCCR1B_CS12);
            break;
        case PWM_PRESCALER_8:
            CLR_BIT(TCCR1B, TCCR1B_CS10);
            SET_BIT(TCCR1B, TCCR1B_CS11);
            CLR_BIT(TCCR1B, TCCR1B_CS12);
            break;
        case PWM_PRESCALER_64:
            
            SET_BIT(TCCR1B, TCCR1B_CS10);
            SET_BIT(TCCR1B, TCCR1B_CS11);
            CLR_BIT(TCCR1B, TCCR1B_CS12);
            break;
        case PWM_PRESCALER_256:
            
            CLR_BIT(TCCR1B, TCCR1B_CS10);
            CLR_BIT(TCCR1B, TCCR1B_CS11);
            SET_BIT(TCCR1B, TCCR1B_CS12);
            break;
        case PWM_PRESCALER_1024:
            
            SET_BIT(TCCR1B, TCCR1B_CS10);
            CLR_BIT(TCCR1B, TCCR1B_CS11);
            SET_BIT(TCCR1B, TCCR1B_CS12);
            break;
        case PWM_PRESCALER_EXT_FALLING:
            
            CLR_BIT(TCCR1B, TCCR1B_CS10);
            SET_BIT(TCCR1B, TCCR1B_CS11);
            SET_BIT(TCCR1B, TCCR1B_CS12);
            break;
        case PWM_PRESCALER_EXT_RISING:
            
            SET_BIT(TCCR1B, TCCR1B_CS10);
            SET_BIT(TCCR1B, TCCR1B_CS11);
            SET_BIT(TCCR1B, TCCR1B_CS12);
            break;
        default:
            break;
        }
        break;

    case PWM_CHANNEL_2:
        switch (prescaler)
        {
        case PWM_PRESCALER_NO_CLOCK:
            
            CLR_BIT(TCCR2, TCCR2_CS20);
            CLR_BIT(TCCR2, TCCR2_CS21);
            CLR_BIT(TCCR2, TCCR2_CS22);
            break;
        case PWM_PRESCALER_8:
            
            CLR_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        case PWM_PRESCALER_32:
            
            SET_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            CLR_BIT(TCCR0, TCCR0_CS02);
            break;
        case PWM_PRESCALER_64:
            
            CLR_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;
        case PWM_PRESCALER_128:
            
            SET_BIT(TCCR0, TCCR0_CS00);
            CLR_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;
        case PWM_PRESCALER_256:
            
            CLR_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;
        case PWM_PRESCALER_1024:
            
            SET_BIT(TCCR0, TCCR0_CS00);
            SET_BIT(TCCR0, TCCR0_CS01);
            SET_BIT(TCCR0, TCCR0_CS02);
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}

void Pwm_SetCompareValue(Pwm_ChannelType channel, u16 value)
{
    switch (channel)
    {
    case PWM_CHANNEL_0:
        OCR0 = value;
        break;
    case PWM_CHANNEL_1A:
        OCR1A = value;
        break;
    case PWM_CHANNEL_1B:
        OCR1B = value;
        break;
    case PWM_CHANNEL_2:
        OCR2 = value;
        break;
    default:
        break;
    }
}

void Pwm_SetTopValue(u16 value)
{
    ICR1 = value;
}
void Pwm_SetCompareMatchOutputMode(Pwm_ChannelType channel, Pwm_SetCompareMatchType mode)
{
    switch (channel)
    {
    case PWM_CHANNEL_0:
        switch (mode)
        {
        case PWM_OC_DICONNECTED:
            CLR_BIT(TCCR0, TCCR0_COM00);
            CLR_BIT(TCCR0, TCCR0_COM01);
            break;
        case PWM_CLEAR_OC_ON_COMPARE_MATCH:
            CLR_BIT(TCCR0, TCCR0_COM00);
            SET_BIT(TCCR0, TCCR0_COM01);
            break;
        case PWM_SET_OC_ON_COMPARE_MATCH:
            SET_BIT(TCCR0, TCCR0_COM00);
            SET_BIT(TCCR0, TCCR0_COM01);
            break;
        default:
            break;
        }
        break;

    case PWM_CHANNEL_1A:
    case PWM_CHANNEL_1B:
        switch (mode)
        {
        case PWM_OC_DICONNECTED:
            CLR_BIT(TCCR1A, TCCR1A_COM1A0);
            CLR_BIT(TCCR1A, TCCR1A_COM1A1);
            CLR_BIT(TCCR1A, TCCR1A_COM1B0);
            CLR_BIT(TCCR1A, TCCR1A_COM1B1);
            break;
        case PWM_CLEAR_OC_ON_COMPARE_MATCH:
            CLR_BIT(TCCR1A, TCCR1A_COM1A0);
            SET_BIT(TCCR1A, TCCR1A_COM1A1);
            CLR_BIT(TCCR1A, TCCR1A_COM1B0);
            CLR_BIT(TCCR1A, TCCR1A_COM1B1);
            break;
        case PWM_SET_OC_ON_COMPARE_MATCH:
            SET_BIT(TCCR1A, TCCR1A_COM1A0);
            SET_BIT(TCCR1A, TCCR1A_COM1A1);
            CLR_BIT(TCCR1A, TCCR1A_COM1B0);
            CLR_BIT(TCCR1A, TCCR1A_COM1B1);
            break;
        default:
            break;
        }
        break;
    case PWM_CHANNEL_2:
        switch (mode)
        {
        case PWM_OC_DICONNECTED:
            CLR_BIT(TCCR2, TCCR2_COM20);
            CLR_BIT(TCCR2, TCCR2_COM21);
            break;
        case PWM_CLEAR_OC_ON_COMPARE_MATCH:
            CLR_BIT(TCCR2, TCCR2_COM20);
            SET_BIT(TCCR2, TCCR2_COM21);
            break;
        case PWM_SET_OC_ON_COMPARE_MATCH:
            SET_BIT(TCCR2, TCCR2_COM20);
            SET_BIT(TCCR2, TCCR2_COM21);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}