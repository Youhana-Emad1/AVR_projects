#include <util/delay.h>

#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LED_interface.h"

/* Free RTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"

// Function to manage the Red LED
void led_red(void* pvParameters)
{
	while (1)
	{
		// Turn on red light
		LED_voidOn(DIO_PORTD, DIO_PIN0, LED_FORWARD_CONNECTION); // Assuming ON is defined in your LED_interface
		// Turn off other lights
		LED_voidOff(DIO_PORTD, DIO_PIN4, LED_FORWARD_CONNECTION);
		LED_voidOff(DIO_PORTD, DIO_PIN7, LED_FORWARD_CONNECTION);
		
		// Red light duration
		vTaskDelay(60000 ); // 60 seconds
	}
}

// Function to manage the Yellow LED
void led_yellow(void* pvParameters)
{
	while (1)
	{
		// Turn off other lights
		LED_voidOff(DIO_PORTD, DIO_PIN0, LED_FORWARD_CONNECTION);
		LED_voidOff(DIO_PORTD, DIO_PIN4, LED_FORWARD_CONNECTION);
		
		// Turn on yellow light
		LED_voidOn(DIO_PORTD, DIO_PIN7, LED_FORWARD_CONNECTION);
		
		// Yellow light duration
		vTaskDelay(10000 ); // 10 seconds
	}
}

// Function to manage the Green LED
void led_green(void* pvParameters)
{
	while (1)
	{
		// Turn off other lights
		LED_voidOff(DIO_PORTD, DIO_PIN0, LED_FORWARD_CONNECTION);
		LED_voidOff(DIO_PORTD, DIO_PIN7, LED_FORWARD_CONNECTION);
		
		// Turn on green light
		LED_voidOn(DIO_PORTD, DIO_PIN4, LED_FORWARD_CONNECTION);
		
		// Green light duration
		vTaskDelay(60000); // 60 seconds
	}
}

int main(void)
{
	// Initialize all LEDs
	LED_voidInit(DIO_PORTD, DIO_PIN0); // LED Red
	LED_voidInit(DIO_PORTD, DIO_PIN4); // LED Green
	LED_voidInit(DIO_PORTD, DIO_PIN7); // LED Yellow

	// Create tasks for each light
	xTaskCreate(led_red, "LED Red", 100, NULL, 1, NULL);
	xTaskCreate(led_yellow, "LED Yellow", 100, NULL, 2, NULL);
	xTaskCreate(led_green, "LED Green", 100, NULL, 3, NULL);

	// Start the scheduler
	vTaskStartScheduler();

	// This point should never be reached
	while (1)
	{
	}
}