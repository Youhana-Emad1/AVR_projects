/*
 * RTOS_TMR_program.c
 *
 * Created: 2/3/2024 9:37:01 AM
 *  Author: Kareem Hussein
 */ 


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* RTOS */
#include "RTOS_TMR_interface.h"
#include "RTOS_TMR_private.h"


static void(*private_pCallBackCTC)(void)=NULL;

void RTOS_TMR_init(void)
{
	// Select Mode = CTC Mode
	CLR_BIT(TCCR2,WGM20);
	SET_BIT(TCCR2,WGM21);
	
	// Enable CTC Interrupt
	SET_BIT(TIMSK,OCIE2);
}


void RTOS_TMR_start(void)
{
	// Select Prescaler Value = 64
	CLR_BIT(TCCR2,CS20);
	CLR_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
}


void RTOS_TMR_stop(void)
{
	CLR_BIT(TCCR2,CS20);
	CLR_BIT(TCCR2,CS21);
	CLR_BIT(TCCR2,CS22);
}


void RTOS_TMR_setCompareMatchValue(u8 compareValue)
{
	OCR2 = compareValue;
}


void RTOS_TMR_setCallBackCTC(void(*ptrToFun)(void))
{
	if(ptrToFun!=NULL)
	{
		private_pCallBackCTC = ptrToFun;
	}
}


// ISR Timer2 output compare match
void __vector_4 (void) __attribute__ ((signal));
void __vector_4 (void)
{
	if(private_pCallBackCTC!=NULL)
	{
		// Call action
		private_pCallBackCTC();
	}
}