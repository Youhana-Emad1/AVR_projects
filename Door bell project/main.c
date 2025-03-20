/*
 * Day1_A.c
 *
 * Created: 01/09/2024 03:31:35 م
 * Author : youhana Emad
 */ 

#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LED_interface.h"
#include "SWITCH_interface.h"


int main(void)
{
	u8 local_u8SW0, local_u8SW1, local_u8SW2;
    LED_voidInit(DIO_PORTC, DIO_PIN2); //LED0
	LED_voidInit(DIO_PORTC, DIO_PIN7); //LED1
	LED_voidInit(DIO_PORTD, DIO_PIN3); //LED2
	
	SWITCH_voidInit(DIO_PORTB, DIO_PIN0);//SW0
	SWITCH_voidInit(DIO_PORTD, DIO_PIN6);//SW1
	DIO_voidActivePinInPullUpResistance(DIO_PORTD, DIO_PIN6);
	SWITCH_voidInit(DIO_PORTD, DIO_PIN2);//SW2
	
    while (1) 
    {
		SWITCH_voidGetState(DIO_PORTB, DIO_PIN0, SWITCH_FORWARD_CONNECTION, &local_u8SW0);
		SWITCH_voidGetState(DIO_PORTD, DIO_PIN6, SWITCH_REVERSE_CONNECTION, &local_u8SW1);
		SWITCH_voidGetState(DIO_PORTD, DIO_PIN2, SWITCH_REVERSE_CONNECTION, &local_u8SW2);
		
		if(local_u8SW0 == SWITCH_PRESSED)
		{
			LED_voidOn(DIO_PORTC, DIO_PIN2, LED_FORWARD_CONNECTION);
		}
		else
		{
			LED_voidOff(DIO_PORTC, DIO_PIN2, LED_FORWARD_CONNECTION);
		}
		
		if(local_u8SW1 == SWITCH_PRESSED)
		{
			LED_voidToggle(DIO_PORTC, DIO_PIN7);
			_delay_ms(1000);
		}
		
		if(local_u8SW2 == SWITCH_PRESSED)
		{
			LED_voidOn(DIO_PORTD, DIO_PIN3, LED_REVERSE_CONNECTION);
		}
		else
		{
			LED_voidOff(DIO_PORTD, DIO_PIN3, LED_REVERSE_CONNECTION);
		}
    }
}

