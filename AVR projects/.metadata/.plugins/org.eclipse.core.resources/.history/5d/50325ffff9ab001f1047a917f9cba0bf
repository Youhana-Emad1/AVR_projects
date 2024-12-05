#define F_CPU 16000000UL
#include <util/delay.h>

/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"
#include "KPD_interface.h"
#include "KPD_config.h"

typedef unsigned char u8;

int main()
{
	LCD_voidInit();
	KPD_voidInit();
	LCD_voidClear();

	u8 PressedKey,Operator = '\0';
	f32 Num1 = 0, Num2 = 0, Res;

	while (1)
	{
		 KPD_voidGetValue(&PressedKey);

		if (PressedKey >= '0' && PressedKey <= '9')
		{
			LCD_voidDisplayString(PressedKey);
			if (Operator == '\0')
			{
				Num1 = Num1 * 10 + (PressedKey - '0');
			}
			else
			{
				Num2 = Num2 * 10 + (PressedKey - '0');
			}
		}
		else if (PressedKey == '+' || PressedKey == '-' || PressedKey == '*' || PressedKey == '/')
		{
			LCD_voidDisplayString(PressedKey);
			Operator = PressedKey;
		}
		else if (PressedKey == '=')
		{
			LCD_voidDisplayString(PressedKey);
			switch (Operator)
			{
				case '+':
				Res = Num1 + Num2;
				break;
				case '-':
				Res = Num1 - Num2;
				break;
				case '*':
				Res = Num1 * Num2;
				break;
				case '/':
				if (Num2 != 0)
				{
					Res = Num1 / Num2;
				}
				else
				{
					LCD_voidClear();
					LCD_voidDisplayString("Division By Zero");
					continue;
				}
				break;
				default:
				LCD_voidClear();
				LCD_voidDisplayString("Invalid Operator!");
			}

			LCD_voidDisplayNumber(Res);
			Num1 = Res;
			Num2 = 0;
			Operator = '\0';
		}
		else if (PressedKey == 'C')
		{
			LCD_voidClear();
			Num1 = 0;
			Num2 = 0;
			Operator = '\0';
		}
	}

	return 0;
}

