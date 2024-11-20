/******************************************************************************
 *                                                                            *
 *************************  SWC     : SSD_program     *************************
 *************************  Date    : 25/02/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/


#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "SSD_interface.h"
#include "SSD_config.h"
#include "SSD_private.h"

static u8 PRV_u8Numbers[10]= {SSD_ZERO, SSD_ONE, SSD_TWO, SSD_THREE, SSD_FOUR, SSD_FIVE, SSD_SEX, SSD_SEVEN, SSD_EIGHT, SSD_NINE};

void SSD_voidInit(void)
{
	DIO_voidSetPortDirection(SSD_DATA_PORT, DIO_PORT_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_OUTPUT);
}


void SSD_voidDisplayNumber(u8 copy_u8DesiredNumber, u8 copy_u8Id)
{
	if(copy_u8DesiredNumber<=9)
	{
		switch(copy_u8Id)
		{
		    case SSD_ONE:
#if SSD_TYPE == SSD_COM_CATHODE
			DIO_voidSetPortValue(SSD_DATA_PORT, PRV_u8Numbers[copy_u8DesiredNumber]);
			DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_LOW);

#elif SSD_TYPE == SSD_COM_ANNODE
			DIO_voidSetPortValue(SSD_DATA_PORT, ~PRV_u8Numbers[copy_u8DesiredNumber]);
			DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_HIGH);
#endif
			break;

		    case SSD_TWO:
#if SSD_TYPE == SSD_COM_CATHODE
			DIO_voidSetPortValue(SSD_DATA_PORT, PRV_u8Numbers[copy_u8DesiredNumber]);
			DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_LOW);

#elif SSD_TYPE == SSD_COM_ANNODE
			DIO_voidSetPortValue(SSD_DATA_PORT, ~PRV_u8Numbers[copy_u8DesiredNumber]);
			DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_HIGH);
#endif
			break;
		}
	}
	else
	{
		// return Error state
	}
}


void SSD_voidDisplayMultiplexedNumber(u8 copy_u8DesiredNumber)
{
	if(copy_u8DesiredNumber<=99)
	{
		u8 local_u8Ones = copy_u8DesiredNumber%10;
		u8 local_u8Tens = copy_u8DesiredNumber/10;

#if SSD_TYPE == SSD_COM_CATHODE
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_HIGH);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_HIGH);
		DIO_voidSetPortValue(SSD_DATA_PORT, PRV_u8Numbers[local_u8Tens]);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_LOW);
		_delay_ms(10);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_HIGH);

		DIO_voidSetPortValue(SSD_DATA_PORT, PRV_u8Numbers[local_u8Ones]);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_LOW);
		_delay_ms(10);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_HIGH);

#elif SSD_TYPE == SSD_COM_ANNODE
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_LOW);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_LOW);
		DIO_voidSetPortValue(SSD_DATA_PORT, ~PRV_u8Numbers[local_u8Tens]);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_HIGH);
		_delay_ms(10);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K1_ENABLE_PIN, DIO_PIN_LOW);

		DIO_voidSetPortValue(SSD_DATA_PORT, ~PRV_u8Numbers[local_u8Ones]);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_HIGH);
		_delay_ms(10);
		DIO_voidSetPinValue(SSD_ENABLE_PORT, SSD_K2_ENABLE_PIN, DIO_PIN_LOW);
#endif
	}
	else
	{
		// return Error state
	}
}
