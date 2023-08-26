/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/

#include <std_types.h>
#include <Data.h>

Data_FrameType ProccessData(Data_Type *data)//function to proccess data and return the state of the data
{
    if (data->frame[7] == 'e')//check if the frame end with 'e'
    {
        //check if the speed is valid by checking if the first 3 characters are numbers and the speed is less than 100
        if ((data->frame[0] < '0' || data->frame[0] > '9') || (data->frame[1] < '0' || data->frame[1] > '9') || (data->frame[2] < '0' || data->frame[2] > '9'))
        {
            return DATA_INVALID_FRAME;//return invalid frame
        }
        else
        {
            //convert the first 3 characters to number and save it in speed variable in data structure
            data->speed = ((u8)data->frame[0] - '0') * 100 + ((u8)data->frame[1] - '0') * 10 + ((u8)data->frame[2] - '0');
            if (data->speed > 100)
            {
                return DATA_INVALID_FRAME;
            }
        }
        switch (data->frame[3])//check the direction of the dc motor and save it in data structure by checking the 4th character
        {
        case 'f': //forward
            data->DC_Dirction = DATA_DIRCTION_FORWARD;
            break;
        case 'b'://backward
            data->DC_Dirction = DATA_DIRCTION_BACKWARD;
            break;
        default://invalid frame
            return DATA_INVALID_FRAME;
            break;
        }
        //check if the servo angle is valid by checking if the 5th and 6th characters are numbers and the angle is less than 45
        if ((data->frame[4] < '0' || data->frame[4] > '9') || (data->frame[5] < '0' || data->frame[5] > '9'))
        {
            return DATA_INVALID_FRAME;
        }
        else
        {
            data->Servo_Angle = ((u8)data->frame[4] - '0') * 10 + ((u8)data->frame[5] - '0');//convert the 5th and 6th characters to number and save it in angle variable in data structure

            if (data->Servo_Angle > 45)
            {
                return DATA_INVALID_FRAME;
            }
        }
        switch (data->frame[6])//check the direction of the servo motor and save it in data structure by checking the 7th character
        {
        case 'r'://right
            data->Servo_Dirction = DATA_DIRCTION_RIGHT;
            break;
        case 'l'://left
            data->Servo_Dirction = DATA_DIRCTION_LEFT;
            break;
        default://invalid frame
            return DATA_INVALID_FRAME;
            break;
        }
    }
    else
    {
        return DATA_INVALID_FRAME;
    }
    return DATA_VALID_FRAME;//return valid frame
}
