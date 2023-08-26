/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/


#ifndef MOTORS_H
#define MOTORS_H




#define DC_MOTOR_FirstPin DIO_PORTC, DIO_PIN0 

#define DC_MOTOR_SecondPin DIO_PORTC, DIO_PIN1



void Motors_Init(void);
void Motors_Handeler(Data_Type * data);

#endif
