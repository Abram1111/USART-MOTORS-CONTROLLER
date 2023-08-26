/********************************************************************************************************/
/*                                      Author     : Abram Gad                                          */
/*                                      Date       : 24/8/2023                                          */
/*                                      version    : V01                                                */
/********************************************************************************************************/
#include <std_types.h>
#include <Macros.h>
#include <Registers.h>
#include <Gie.h>

#define SREG_I 7

void Gie_Enable(void)//function to enable global interrupt
{
    SET_BIT(SREG, SREG_I);//set bit 7 in SREG register to enable global interrupt
}

void Gie_Disable(void)
{
    CLR_BIT(SREG, SREG_I);//clear bit 7 in SREG register to disable global interrupt
}

