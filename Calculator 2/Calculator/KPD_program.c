
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "KPD_config.h"
#include "KPD_interface.h"
#include <util/delay.h>

void KPD_VidInit(void)
{
	//Set Columns as Output
	DIO_VidSetPinDirection(KPD_PORT_Col,KPD_COLUMN_0,Output);
	DIO_VidSetPinDirection(KPD_PORT_Col,KPD_COLUMN_1,Output);
	DIO_VidSetPinDirection(KPD_PORT_Col,KPD_COLUMN_2,Output);
	DIO_VidSetPinDirection(KPD_PORT_Col,KPD_COLUMN_3,Output);
	//Set Columns as PinHigh
	DIO_VidSetPinValue(KPD_PORT_Col,KPD_COLUMN_0,PinHigh);
	DIO_VidSetPinValue(KPD_PORT_Col,KPD_COLUMN_1,PinHigh);
	DIO_VidSetPinValue(KPD_PORT_Col,KPD_COLUMN_2,PinHigh);
	DIO_VidSetPinValue(KPD_PORT_Col,KPD_COLUMN_3,PinHigh);

	//Set Row as Input
	DIO_VidSetPinDirection(KPD_PORT_Row,KPD_ROW_0,Input);
	DIO_VidSetPinDirection(KPD_PORT_Row,KPD_ROW_1,Input);
	DIO_VidSetPinDirection(KPD_PORT_Row,KPD_ROW_2,Input);
	DIO_VidSetPinDirection(KPD_PORT_Row,KPD_ROW_3,Input);
	//Set Row as PinHigh
	DIO_VidSetPinValue(KPD_PORT_Row,KPD_ROW_0,PinHigh);
	DIO_VidSetPinValue(KPD_PORT_Row,KPD_ROW_1,PinHigh);
	DIO_VidSetPinValue(KPD_PORT_Row,KPD_ROW_2,PinHigh);
	DIO_VidSetPinValue(KPD_PORT_Row,KPD_ROW_3,PinHigh);



}
u8 Kpd_U8GetPressedKey(void)
{
	/*************value if button was not pressed******************/
	u8 Local_u8_Pressed_Key=KPD_NO_PRESSED_KEY;

	/********************counter for (forloop)********************/
	u8  Local_u8_Column_Counter,Local_u8_Row_Counter;

	/**************************variable for pin state*************************/
	u8  Local_u8_Pint_State;

	/*******************KEY_PAD_VALUES******************************/
   static u8 Local_u8_Kpd_Arr[ROW_NUM][COLUMN_NUM]=KPD_ARR_VAL;

	/*******************KEY_COLUMN_Array******************************/
   static u8 Local_u8_Kpd_Column_Array[COLUMN_NUM]={KPD_COLUMN_0,KPD_COLUMN_1,KPD_COLUMN_2,KPD_COLUMN_3};

	/*******************KEY_ROWS_Array******************************/
   static  u8 Local_u8_Kpd_Rows_Array[ROW_NUM]={KPD_ROW_0,KPD_ROW_1,KPD_ROW_2,KPD_ROW_3};



	for(Local_u8_Column_Counter=0;Local_u8_Column_Counter<COLUMN_NUM;Local_u8_Column_Counter++)
	{
		/**************ACTIVATE CURRENT COLUMN************************/

		DIO_VidSetPinValue(KPD_PORT_Col,Local_u8_Kpd_Column_Array[Local_u8_Column_Counter],PinLow);

		/*************READ CURRENT ROW****************/
		for(Local_u8_Row_Counter=0;Local_u8_Row_Counter<ROW_NUM;Local_u8_Row_Counter++)
		{
			DIO_VidgetPinValue(KPD_PORT_Row,Local_u8_Kpd_Rows_Array[Local_u8_Row_Counter],&Local_u8_Pint_State);

			 /*****CHECK IF KEY IS PREESED*******/

			if(Local_u8_Pint_State==PinLow)
			{
				Local_u8_Pressed_Key=Local_u8_Kpd_Arr[Local_u8_Row_Counter][Local_u8_Column_Counter];

				while(Local_u8_Pint_State==PinLow)
				{
					DIO_VidgetPinValue(KPD_PORT_Row,Local_u8_Kpd_Rows_Array[Local_u8_Row_Counter],&Local_u8_Pint_State);
				}
				return Local_u8_Pressed_Key;
			}
		}
		/*******DEACTIVATE CURRENT COLUMN***********/
		DIO_VidSetPinValue(KPD_PORT_Col,Local_u8_Kpd_Column_Array[Local_u8_Column_Counter],PinHigh);

	}

	return Local_u8_Pressed_Key;
}



