/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/
#include <std_types.h>
#include <Dio.h>
#include "cpu_freq.h"
#include <Pwm.h>
#include <Data.h>
#include <Motors.h>
void Motors_Init(void)//initialize dc motor
{
    //initialize pins of dc motor to output
    Dio_SetPinMode(DC_MOTOR_FirstPin, DIO_PIN_OUTPUT);
    Dio_SetPinMode(DC_MOTOR_SecondPin, DIO_PIN_OUTPUT);
    Pwm_Init(PWM_CHANNEL_1A);//initialize pwm channel 1A
    Pwm_SetPrescaler(PWM_CHANNEL_1A, PWM_PRESCALER_64);//set prescaler to 64
    Pwm_SetTopValue(2500);//set top value to 2500 so that the period is 20ms
    Pwm_SetCompareValue(PWM_CHANNEL_1A, 214);//set compare value to 214 so that the angle is 0 degree
    Pwm_Init(PWM_CHANNEL_2);// initialize pwm channel 2
    Pwm_SetTopValue(250);//set top value to 250
}
static void Motors_ServoSetAngle(u8 angle, Data_DircrionType dirction)//set angle of servo motor
{
    u16 value = 0;//variable to hold the value of the compare register
    if (dirction == DATA_DIRCTION_RIGHT)//if the dirction is right
    {
        value = 214 + angle;//increase the value of the compare register by the angle
    }
    else//if the dirction is left
    {
        value = 214 - angle;//decrease the value of the compare register by the angle
    }
    Pwm_SetCompareValue(PWM_CHANNEL_1A, value);//set the compare register to the value to change the angle of the servo motor
}
static void Motors_DcSetDirection(Data_DircrionType direction)//set dirction of dc motor
{

    if (direction == DATA_DIRCTION_FORWARD)//if the dirction is forward
    {
        Dio_SetPinLevel(DC_MOTOR_FirstPin, STD_HIGH);
        Dio_SetPinLevel(DC_MOTOR_SecondPin, STD_LOW);
    }
    else
    {
        Dio_SetPinLevel(DC_MOTOR_FirstPin, STD_LOW);
        Dio_SetPinLevel(DC_MOTOR_SecondPin, STD_HIGH);
    }
}

static void Motors_DcSetSpeed(u8 speed)//set dirction of dc motor
{
    //set speed of dc motor by setting the duty cycle of the pwm
    u16 value = (speed*250)/100;//calculate the value of the duty cycle
    Pwm_SetCompareValue(PWM_CHANNEL_2, value);//set compare value to the speed to change the duty cycle of the pwm
}
void Motors_Handeler(Data_Type * data)
{

    Motors_ServoSetAngle(data->Servo_Angle, data->Servo_Dirction);
    Motors_DcSetDirection(data->DC_Dirction);
    Motors_DcSetSpeed(data->speed);
}

