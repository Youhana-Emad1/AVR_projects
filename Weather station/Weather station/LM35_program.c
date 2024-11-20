/******************************************************************************
 *                                                                            *
 *************************  SWC     : LM35_program    *************************
 *************************  Date    : 14/01/2024      *************************
 *************************  Author  : kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "ADC_interface.h"
#include "DIO_interface.h"

/* HAL */
#include "LM35_interface.h"
#include "LM35_config.h"


void LM35_voidInit(void)
{
	DIO_voidSetPinDirection(DIO_PORTA, LM35_CHANNEL_NUM, DIO_PIN_INPUT);
	ADC_voidInit(ADC_REFERENCE_AVCC);
}


void LM35_voidGetTemperature(u8* copy_u8Temperature)
{
	if(copy_u8Temperature!=NULL)
	{
		u16 local_u16DigitalVal, local_u16AnalogVal;

		ADC_voidGetDigitalValue(LM35_CHANNEL_NUM, &local_u16DigitalVal);
		
		// depend on Refrence volt AVCC (5V)
		local_u16AnalogVal = ((u32)local_u16DigitalVal*5000)/1024;

		*copy_u8Temperature = local_u16AnalogVal/10;
	}
	else
	{
		// return Error State
	}
}
