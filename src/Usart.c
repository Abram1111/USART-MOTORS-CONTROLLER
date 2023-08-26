/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/
#include <std_types.h>
#include <Macros.h>
#include <Registers.h>
#include <stdarg.h>
#include <Dio.h>
#include <cpu_freq.h>
#include <Interrupts.h>
#include <Usart_private.h>
#include <Usart_cfg.h>
#include <Usart.h>
#include <Utils.h>

void (*Usart_ReceiveCallback)(u8 data);
void (*Usart_TransmitCallback)(void);
void (*Usart_TransmitEmptyCallback)(void);

ISR(VECTOR_USART_RX)
{
    Usart_ReceiveCallback(UDR);
}

ISR(VECTOR_USART_TX)
{
    Usart_TransmitCallback();
}

ISR(VECTOR_USART_EMPTY)
{
    Usart_TransmitEmptyCallback();
}

void Usart_Init(void)
{
    u8 temp = 0;
    /* Select UCSRC Register */
    SET_BIT(temp, UCSRC_URSEL);
    /* Data Size Select */
#if USART_CHAR_SIZE == USART_CHAR_SIZE_8_BIT
    SET_BIT(temp, UCSRC_UCSZ0);
    SET_BIT(temp, UCSRC_UCSZ1);
    CLR_BIT(UCSRB, UCSRB_UCSZ2);
#elif USART_CHAR_SIZE == USART_CHAR_SIZE_7_BIT
    
    CLR_BIT(temp, UCSRC_UCSZ0);
    SET_BIT(temp, UCSRC_UCSZ1);
    CLR_BIT(UCSRB, UCSRB_UCSZ2);
#elif USART_CHAR_SIZE == USART_CHAR_SIZE_6_BIT
    
    SET_BIT(temp, UCSRC_UCSZ0);
    CLR_BIT(temp, UCSRC_UCSZ1);
    CLR_BIT(UCSRB, UCSRB_UCSZ2);
#elif USART_CHAR_SIZE == USART_CHAR_SIZE_5_BIT
    
    CLR_BIT(temp, UCSRC_UCSZ0);
    CLR_BIT(temp, UCSRC_UCSZ1);
    CLR_BIT(UCSRB, UCSRB_UCSZ2);
#else
#error "USART: INVALID CHAR SIZE"
#endif

#if USART_MODE == USART_SYNC
    SET_BIT(temp, UCSRC_UMSEL);
#if USART_CLK_POLARITY == USART_POLARITY_T_FALLING_R_RISING
    SET_BIT(temp, UCSRC_UCPOL);
#endif
#endif

#if USART_PARITY == USART_PARITY_EVEN
    SET_BIT(temp, UCSRC_UPM1);
    CLR_BIT(temp, UCSRC_UPM0);
#elif USART_PARITY == USART_PARITY_ODD
    
    SET_BIT(temp, UCSRC_UPM1);
    SET_BIT(temp, UCSRC_UPM0);
#endif

#if USART_STOP_BIT == USART_2_STOP_BIT
    SET_BIT(temp, UCSRC_USBS);
#endif

    UCSRC = temp;

    /* Baud Rate Select */
    u16 baud = (F_CPU / ((u32)16 * USART_BAUD_RATE)) - 1;
    UBRRL = (u8)baud;
    UBRRH = (u8)((baud >> 8) & 0x0F);

    /* Rx Enable */
#if USART_RECEIVER_ENABLE == USART_ON
    SET_BIT(UCSRB, UCSRB_RXEN);
    Dio_SetPinMode(DIO_PORTD, DIO_PIN0, DIO_PIN_INPUT_FLOATING);
#endif

    /* Tx Enable */
#if USART_TRANSMITTER_ENABLE == USART_ON
    SET_BIT(UCSRB, UCSRB_TXEN);
    Dio_SetPinMode(DIO_PORTD, DIO_PIN1, DIO_PIN_OUTPUT);
#endif
}

void Usart_Transmit(u8 data)
{
    while (GET_BIT(UCSRA, 5) == 0)
        ;
    UDR = data;
    while (GET_BIT(UCSRA, 6) == 0)
        ;
    SET_BIT(UCSRA, 6);
}

void Usart_TransmitAsync(u8 data)
{
    while (GET_BIT(UCSRA, 5) == 0)
        ;
    UDR = data;
}

u8 Usart_Receive(void)
{
    while (GET_BIT(UCSRA, 7) == 0)
        ;
    return UDR;
}

Usart_StateType Usart_ReceiveAsync(u8 *data)
{
    Usart_StateType flag = USART_NOT_COMPLETE;
    if (GET_BIT(UCSRA, 7) == 1)
    {
        *data = UDR;
        flag = USART_COMPLETE;
    }
    return flag;
}

void Usart_EnableNotification(Usart_InterruptSourceType source)
{
    switch (source)
    {
    case USART_INT_SOURCE_RX:
        SET_BIT(UCSRB, UCSRB_RXCIE);
        break;
    case USART_INT_SOURCE_TX:
        SET_BIT(UCSRB, UCSRB_TXCIE);
        break;
    case USART_INT_SOURCE_EMPTY:
        SET_BIT(UCSRB, UCSRB_UDRIE);
        break;
    default:
        break;
    }
}

void Usart_DisableNotification(Usart_InterruptSourceType source)
{
    switch (source)
    {
    case USART_INT_SOURCE_RX:
        CLR_BIT(UCSRB, UCSRB_RXCIE);
        break;
    case USART_INT_SOURCE_TX:
        CLR_BIT(UCSRB, UCSRB_TXCIE);
        break;
    case USART_INT_SOURCE_EMPTY:
        CLR_BIT(UCSRB, UCSRB_UDRIE);
        break;
    default:
        break;
    }
}

void Usart_SetCallbackReceive(void (*callback)(u8 data))
{
    Usart_ReceiveCallback = callback;
}
void Usart_SetCallbackTransmit(void (*callback)(void))
{
    Usart_TransmitCallback = callback;
}
void Usart_SetCallbackEmpty(void (*callback)(void))
{
    Usart_TransmitEmptyCallback = callback;
}

void Usart_SendString(const u8 *str)
{
    while (*str != 0)
    {
        Usart_Transmit(*str);
        str++;
    }
}

void Usart_SendNumber(s64 num)
{
    u64 reversed = 0;
    u8 counter = 0;
    if (num < 0)
    {
        Usart_Transmit('-');
        num *= -1;
    }
    do
    {
        reversed = reversed * 10 + (num % 10);
        num = num / 10;
        counter++;
    } while (num != 0);
    do
    {
        Usart_Transmit(reversed % 10 + '0');
        reversed = reversed / 10;
        counter--;
    } while (counter != 0);
}

void Usart_Print(const u8 *str, ...)
{
    u8 i = 0;
    va_list valist;
    va_start(valist, str);
    while (str[i] != '\0')
    {
        if (str[i] == '%')
        {
            u8 arr[32];
            u8 count;
            i++;
            switch (str[i])
            {
            case 'c':
                Usart_Transmit((u8)va_arg(valist, int));
                break;
            case 'd':
                Usart_SendNumber(va_arg(valist, int));
                break;
            case 'u':
                if (str[i + 1] == 'l')
                {
                    i++;
                    Usart_SendNumber(va_arg(valist, unsigned long));
                }
                else
                {
                    Usart_SendNumber(va_arg(valist, unsigned int));
                }
                break;
            case 'l':
                Usart_SendNumber(va_arg(valist, long));
                break;
            case 'x':
                if (str[i + 1] == 'l')
                {
                    i++;
                    count = Utils_NumberToHex(va_arg(valist, unsigned long), arr);
                }
                else
                {
                    count = Utils_NumberToHex(va_arg(valist, unsigned int), arr);
                }
                for (u8 j = count; j > 0; j--)
                {
                    Usart_Transmit(arr[j]);
                }
                Usart_Transmit(arr[0]);
                break;
            case 'b':
                if (str[i + 1] == 'l')
                {
                    i++;
                    count = Utils_NumberToBin(va_arg(valist, unsigned long), arr);
                }
                else
                {
                    count = Utils_NumberToBin(va_arg(valist, unsigned int), arr);
                }
                for (u8 j = count; j > 0; j--)
                {
                    Usart_Transmit(arr[j]);
                }
                Usart_Transmit(arr[0]);
                break;
            default:
                if (str[i] == '\0')
                {
                    i--;
                }
                else
                {
                    Usart_Transmit(str[i]);
                }
                break;
            }
        }
        else
        {
            Usart_Transmit(str[i]);
        }
        i++;
    }
    va_end(valist);
}
