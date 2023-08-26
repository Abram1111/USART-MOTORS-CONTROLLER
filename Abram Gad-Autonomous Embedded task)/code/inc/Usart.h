/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/


#ifndef INC_USART_H_
#define INC_USART_H_

typedef enum
{
    USART_NOT_COMPLETE,
    USART_COMPLETE
} Usart_StateType;//type to hold the state of the usart

typedef enum
{
    USART_INT_SOURCE_RX,
    USART_INT_SOURCE_TX,
    USART_INT_SOURCE_EMPTY
} Usart_InterruptSourceType;//type to hold the interrupt source of the usart

void Usart_Init(void);//function to initialize the usart
void Usart_Transmit(u8 data);//function to transmit data using usart
void Usart_TransmitASync(u8 data);//function to transmit data using usart without waiting
u8 Usart_Receive(void);//function to receive data using usart
Usart_StateType Usart_ReceiveAsync(u8 *data);//function to receive data using usart without waiting and return the state of the usart
void Usart_EnableNotification(Usart_InterruptSourceType source);//function to enable interrupt of usart
void Usart_DisableNotification(Usart_InterruptSourceType source);//function to disable interrupt of usart
void Usart_SetCallbackReceive(void (*callback)(u8 data));//function to set callback function to be called when usart receive data
void Usart_SetCallbackTransmit(void (*callback)(void));//function to set callback function to be called when usart transmit data
void Usart_SetCallbackEmpty(void (*callback)(void));
void Usart_SendString(const u8 *str);//function to send string using usart
void Usart_SendNumber(s64 num);//function to send number using usart
void Usart_Print(const u8 *str, ...);//function to print string using usart like printf function with arguments

#define ENABLE_DEBUG 0
#if ENABLE_DEBUG == 1
#define DEBUG_PRINT(...) Usart_Print(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif

#endif /* INC_USART_H_ */
