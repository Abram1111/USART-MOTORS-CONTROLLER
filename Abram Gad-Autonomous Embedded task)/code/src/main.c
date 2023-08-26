/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/

/********************************************************************************************************/
/*                                       INCLUDES                                                       */
/********************************************************************************************************/
#include <std_types.h>
#include <Macros.h>
#include <cpu_freq.h>
#include <Registers.h>
#include <util/delay.h>
#include <Dio.h>
#include <Gie.h>
#include <Interrupts.h>
#include <Gpt.h>
#include <Pwm.h>
#include <Usart.h>
#include <Lcd.h>
#include <Data.h>
#include <Motors.h>
/********************************************************************************************************/

/********************************************************************************************************/
/*                                       DEFINES                                                        */
/********************************************************************************************************/
volatile u8 g_data = 0;
volatile u8 received_flag = 0;
volatile u8 SecondFlag = 0;
volatile u16 timerCounter = 0;
volatile u8 frameCounter = 0;
/********************************************************************************************************/

/********************************************************************************************************/
/*                                      HANDELER FUNCTIONS                                              */
/********************************************************************************************************/
void TimerHandeler()
{
	
	timerCounter++;//overflow every 250 micro second
	
	if (timerCounter == 4000)//one 1 second every 4000 overflow
	{
		
		timerCounter = 0;//reset counter
		SecondFlag = 1;//set flag to 1 to indicate that 1 second has passed
	}
}

void HandlerUsart(u8 data)
{
	received_flag = 1;//set flag to 1 to indicate that data has been received
	g_data = data; //save data in global variable
}
/********************************************************************************************************/
int main(void)
{
	/* Timer Variables */
		u8 Second = 0;
		u8 Minute = 0;
		u8 Hour = 0;
	/*******************/
	u8 validation = 0;
	Data_Type data;
    /* Initialisation */
	Lcd_Init();
	Usart_Init();
	Gpt_Init();
	Motors_Init();
	Gie_Enable();
	/*******************/
	Lcd_DisplayClear();
	Lcd_SetCursorPosition(1, 1);
	Lcd_DisplayString((u8 *)"Time:00:00:00AM");
	Gpt_EnableNotification(GPT_INT_SOURCE_TIM0_COMP, TimerHandeler); // enable timer interrupt
	Gpt_Start(GPT_CHANNEL_TIM0, 250); // start timer with 250 micro second
	Usart_EnableNotification(USART_INT_SOURCE_RX); // enable usart receve interrupt
	Usart_SetCallbackReceive(HandlerUsart);// set usart callback function

	while (1)
	{
		if (SecondFlag)//check if 1 second has passed
		{
			SecondFlag = 0;//reset flag
			Second++;//increment second

			if (Second == 60)//check if 1 minute has passed
			{
				Second = 0;//reset second
				Minute++;//increment minute
				if (Minute == 60)//check if 1 hour has passed
				{
					Minute = 0;//reset minute
					Hour++;//increment hour
				}
			}
			Lcd_TimerDisplay(Hour, Minute, Second);//display time on lcd
		}
		if (received_flag)//check if data has been received
		{
			received_flag = 0;//reset flag
			Usart_Transmit(g_data);//for testing
			data.frame[frameCounter] = g_data;//save data in frame
			frameCounter++;//increment frame counter
			if (frameCounter == 8)//check if frame is complete
			{
				frameCounter = 0;//reset frame counter

				validation = ProccessData(&data);//validate frame
				if (validation == DATA_VALID_FRAME)//check if frame is valid
				{
					Lcd_ClearRow(0);//clear first row
					Lcd_SetCursorPosition(0, 0);//set cursor position
					Motors_Handeler(&data);//handle data
					Lcd_Print((u8 *)"Speed:%d dir:%d", data.speed, data.Servo_Angle);//display speed and  angle on lcd
				}
				else
				{
					Lcd_ClearRow(0);//clear first row
					Lcd_SetCursorPosition(0, 0);	//set cursor position
					Lcd_DisplayString((u8 *)"Invalid Frame");//display invalid frame on lcd
				}
			}
		}
	}
}
