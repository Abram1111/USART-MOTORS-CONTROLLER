/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/

#include <std_types.h>
#include <Lcd.h>
u8 Utils_NumberToHex(u32 number, u8 arr[])
{
    u8 counter = 0;
    u8 remainder;
    do
    {
        remainder = number % 16;
        number /= 16;
        if (remainder < 10)
        {
            arr[counter] = remainder + '0';
        }
        else
        {
            arr[counter] = remainder - 10 + 'A';
        }
        counter++;
    } while (number != 0);
    return counter - 1;
}

u8 Utils_NumberToBin(u32 number, u8 arr[])
{
    u8 counter = 0;
    do
    {
        arr[counter] = number % 2 + '0';
        number /= 2;
        counter++;
    } while (number != 0);
    return counter - 1;
}