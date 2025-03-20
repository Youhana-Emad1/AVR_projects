/*
 * main.c
 *
 *  Created on: Dec 1, 2024
 *      Author: tony6
 */
#include <util/delay.h>

#define F_CPU 16000000UL

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LED_interface.h"
#include "SSD_interface.h"
#include "SSD_private.h"
#include "SSD_config.h"

/* RTOS */
#include "RTOS_config.h"
#include "RTOS_interface.h"
#include "RTOS_private.h"
#include "RTOS_TMR_interface.h"
#include "RTOS_TMR_private.h"
#include "GI_interface.h"





void leds(void)
{
	// ------------Red Led Pin 0 Port D ------------------
	LED_voidOff(DIO_PORTD, DIO_PIN4, LED_FORWARD_CONNECTION); // led yellow off
	LED_voidOff(DIO_PORTD, DIO_PIN7, LED_FORWARD_CONNECTION); // led green off
	LED_voidOn(DIO_PORTD, DIO_PIN0, LED_FORWARD_CONNECTION);
	for (int i = 1; i <= 60; i++)
	{
		SSD_voidDisplayMultiplexedNumber(i);
		_delay_ms(5000);
	}

	// ------------ Yellow Led Pin 4 Port D ------------------
	LED_voidOff(DIO_PORTD, DIO_PIN0, LED_FORWARD_CONNECTION); // led red off
	LED_voidOff(DIO_PORTD, DIO_PIN7, LED_FORWARD_CONNECTION); // led green off
	LED_voidOn(DIO_PORTD, DIO_PIN4, LED_FORWARD_CONNECTION);
	for (int i = 1; i <= 5; i++)
	{
		SSD_voidDisplayMultiplexedNumber(i);
		_delay_ms(5000);
	}

	// ------------Green Led Pin 7 Port D ------------------
	LED_voidOff(DIO_PORTD, DIO_PIN0, LED_FORWARD_CONNECTION); // led red off
	LED_voidOff(DIO_PORTD, DIO_PIN4, LED_FORWARD_CONNECTION); // led yellow off
	LED_voidOn(DIO_PORTD, DIO_PIN7, LED_FORWARD_CONNECTION);
	for (int i = 1; i <= 60; i++)
	{
		SSD_voidDisplayMultiplexedNumber(i);
		_delay_ms(5000);
	}
	// ------------ Yellow Led Pin 4 Port D ------------------
	LED_voidOff(DIO_PORTD, DIO_PIN0, LED_FORWARD_CONNECTION); // led red off
	LED_voidOff(DIO_PORTD, DIO_PIN7, LED_FORWARD_CONNECTION); // led green off
	LED_voidOn(DIO_PORTD, DIO_PIN4, LED_FORWARD_CONNECTION);
	for (int i = 1; i <= 5; i++)
	{
		SSD_voidDisplayMultiplexedNumber(i);
		_delay_ms(5000);
	}
}

//--------------main function -----------------------------
int main(void)
{
	SSD_voidInit();
	LED_voidInit(DIO_PORTD, DIO_PIN0);
	LED_voidInit(DIO_PORTD, DIO_PIN4);
	LED_voidInit(DIO_PORTD, DIO_PIN7);
	while (1)
	{
			RTOS_createTask(0, 1, &leds);

			RTOS_start();
	}

	return 0;
}


