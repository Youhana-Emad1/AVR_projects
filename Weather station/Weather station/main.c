/*  
 * Weather Station.c   
 *  
 * Created: 9/7/2024 11:55:07 PM   
 * Author : tony6   
 */   

/* UTILES_LIB */  
#define F_CPU 16000000UL  
#include <util/delay.h>  
#include "STD_TYPES.h"  
#include "BIT_MATH.h"  
#include "VECTOR_NUM.h"  

/* MCAL */  
#include "ADC_interface.h"  
#include "ADC_register.h"  
#include "DIO_interface.h"  
#include "DIO_register.h"  
#include "PWM_interface.h"  

/* HAL */  
#include "DCM_interface.h"  
#include "DCM_config.h"  
#include "LCD_interface.h"  
#include "LCD_config.h"  
#include "LCD_private.h"  
#include "LM35_interface.h"  
#include "LM35_config.h"  
#include "PWM_config.h"  
#include "PWM_private.h"  
#include "PWM_register.h"  

int main(void)
{
	// Initialize the LCD
	LCD_voidInit();

	// Initialize the ADC and LM35 sensor
	LM35_voidInit();

	// Initialize the DC motor
	DCM_voidInit(DCM_MOTOR_A);
	
		// Initialize the PWM Signal
		PWM_voidInitChannel_0();
		
	while (1)
	{
		// Read the temperature from the LM35 sensor
		u8 temperature;
		LM35_voidGetTemperature(&temperature);

		// Control the DC motor based on the temperature
		u8 duty_cycle;
		if (temperature < 20)
		{
			duty_cycle = 50;
		}
		else if (temperature < 25)
		{
			duty_cycle = 75;
		}
		else if (temperature < 30)
		{
			duty_cycle = 90;
		}
		else if (temperature <= 40)
		{
			duty_cycle = 100;
		}
		else
		{
			duty_cycle = 0;
		}
		DCM_voidOn(DCM_MOTOR_A, DCM_CLOCK_WISE);
		DCM_voidControlSpeed(DCM_MOTOR_A, DCM_CLOCK_WISE, duty_cycle);

		// Display the temperature on the LCD
		LCD_voidClear();
		LCD_voidGoToSpecificPosition(LCD_LINE_ONE, 0);
		LCD_voidDisplayNumber(temperature);
		LCD_voidDisplayString(" C");

		_delay_ms(1000);
	}

	return 0;
}