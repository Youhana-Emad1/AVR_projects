#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "DIO_register.h"

/* HAL */
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"

int main(void)
{
	LCD_voidInit();
	while (1)
	{
		LCD_voidClear();
		LCD_voidDisplayString("Hello World");
		_delay_ms(5000);
		LCD_voidClear();
		LCD_voidDisplayString("Trust me I'm an:");
		LCD_voidGoToSpecificPosition(LCD_LINE_TWO, 0);
		LCD_voidDisplayString("' Engineer !!! '");
		_delay_ms(5000);
	}
}