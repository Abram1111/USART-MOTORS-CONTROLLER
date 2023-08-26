/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/
#ifndef DATA_PROCCESS_H_
#define DATA_PROCCESS_H_

typedef enum
{
    DATA_DIRCTION_FORWARD,
    DATA_DIRCTION_BACKWARD,
    DATA_DIRCTION_RIGHT,
    DATA_DIRCTION_LEFT
} Data_DircrionType;//enum to hold the dirction of the dc motor and the servo motor

typedef enum
{
    DATA_VALID_FRAME,
    DATA_INVALID_FRAME
} Data_FrameType;//enum to hold the state of the frame

typedef struct
{
    u16 speed;
    Data_DircrionType DC_Dirction;
    Data_DircrionType Servo_Dirction;
    u8 Servo_Angle;
    u8 frame[8];
} Data_Type;//struct to hold the data

Data_FrameType ProccessData(Data_Type *data);//function to proccess the data

#endif // DATA_H