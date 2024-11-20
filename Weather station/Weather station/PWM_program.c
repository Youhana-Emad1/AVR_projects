/******************************************************************************
 *                                                                            *
 *************************  SWC     : PWM_program     *************************
 *************************  Date    : 14/01/2024      *************************
 *************************  Author  : kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "VECTOR_NUM.h"

/* MCAL */
#include "PWM_interface.h"
#include "PWM_config.h"
#include "PWM_private.h"
#include "PWM_register.h"


void PWM_voidInitChannel_0(void)
{
#if PWM_CHANNEL_0_MODE == PWM_CHANNEL_0_FAST_MODE
    // Select Mode = FAST PWM Mode 
	SET_BIT(TCCR0_REG,WGM00);
	SET_BIT(TCCR0_REG,WGM01);
	
#elif PWM_CHANNEL_0_MODE == PWM_CHANNEL_0_PHASE_CORRECT_MODE
    // Select Mode = PWM phase correct Mode 
	SET_BIT(TCCR0_REG,WGM00);
	CLR_BIT(TCCR0_REG,WGM01);
#endif

#if PWM_CHANNEL_0_OUTPUT_MODE == PWM_CHANNEL_0_NONINVERTING
    // Select Non Inverting Mode
    CLR_BIT(TCCR0_REG,COM00);
    SET_BIT(TCCR0_REG,COM01);
#elif PWM_CHANNEL_0_OUTPUT_MODE == PWM_CHANNEL_0_INVERTING
   // Select Inverting Mode
    SET_BIT(TCCR0_REG,COM00);
    SET_BIT(TCCR0_REG,COM01);
#endif
}


void PWM_voidInitChannel_1A(void)
{
	// Select Mode = Fast PWM Mode(14)	
	CLR_BIT(TCCR1A_REG,WGM10);
    SET_BIT(TCCR1A_REG,WGM11);
	SET_BIT(TCCR1B_REG,WGM12);
	SET_BIT(TCCR1B_REG,WGM13);
	
#if PWM_CHANNEL_1A_OUTPUT_MODE == PWM_CHANNEL_1A_NONINVERTING
    // Select Non Inverting Mode
	CLR_BIT(TCCR1A_REG,COM1A0);
    SET_BIT(TCCR1A_REG,COM1A1);
#elif PWM_CHANNEL_1A_OUTPUT_MODE == PWM_CHANNEL_1A_INVERTING
    // Select Inverting Mode
	SET_BIT(TCCR1A_REG,COM1A0);
    SET_BIT(TCCR1A_REG,COM1A1);
#endif
}


void PWM_voidInitChannel_1B(void)
{
	// Select Mode = Fast PWM Mode(15)	
	SET_BIT(TCCR1A_REG,WGM10);
    SET_BIT(TCCR1A_REG,WGM11);
	SET_BIT(TCCR1B_REG,WGM12);
	SET_BIT(TCCR1B_REG,WGM13);
	
#if PWM_CHANNEL_1B_OUTPUT_MODE == PWM_CHANNEL_1B_NONINVERTING
    // Select Non Inverting Mode
	CLR_BIT(TCCR1A_REG,COM1B0);
    SET_BIT(TCCR1A_REG,COM1B1);
#elif PWM_CHANNEL_1B_OUTPUT_MODE == PWM_CHANNEL_1B_INVERTING
    // Select Inverting Mode
	SET_BIT(TCCR1A_REG,COM1B0);
    SET_BIT(TCCR1A_REG,COM1B1);
#endif
}


void PWM_voidInitChannel_2(void)
{
#if PWM_CHANNEL_2_MODE == PWM_CHANNEL_2_FAST_MODE
    // Select Mode = FAST PWM Mode 
	SET_BIT(TCCR2_REG,WGM20);
	SET_BIT(TCCR2_REG,WGM21);
	
#elif PWM_CHANNEL_2_MODE == PWM_CHANNEL_2_PHASE_CORRECT_MODE
    // Select Mode = PWM phase correct Mode 
	SET_BIT(TCCR2_REG,WGM20);
	CLR_BIT(TCCR2_REG,WGM21);
#endif

#if PWM_CHANNEL_2_OUTPUT_MODE == PWM_CHANNEL_2_NONINVERTING
    // Select Non Inverting Mode
    CLR_BIT(TCCR2_REG,COM20);
    SET_BIT(TCCR2_REG,COM21);
#elif PWM_CHANNEL_2_OUTPUT_MODE == PWM_CHANNEL_2_INVERTING
   // Select Inverting Mode
    SET_BIT(TCCR2_REG,COM20);
    SET_BIT(TCCR2_REG,COM21);
#endif
}


void PWM_voidGenerate_PWM_Channel_0(u8 copy_u8DutyCycle)
{
	if(copy_u8DutyCycle<=100)
	{
		#if PWM_CHANNEL_0_MODE == PWM_CHANNEL_0_FAST_MODE
		
		#if PWM_CHANNEL_0_OUTPUT_MODE == PWM_CHANNEL_0_NONINVERTING
		OCR0_REG = (((u16)copy_u8DutyCycle*256)/100)-1;
		#elif PWM_CHANNEL_0_OUTPUT_MODE == PWM_CHANNEL_0_INVERTING
		copy_u8DytyCycle = 100 - copy_u8DytyCycle;
		OCR0_REG = (((u16)copy_u8DutyCycle*256)/100)-1;
		#endif
		
		#elif PWM_CHANNEL_0_MODE == PWM_CHANNEL_0_PHASE_CORRECT_MODE
		#if PWM_CHANNEL_0_OUTPUT_MODE == PWM_CHANNEL_0_NONINVERTING
		OCR0_REG = (((u16)copy_u8DutyCycle*510)/200)-2;
		#elif PWM_CHANNEL_0_OUTPUT_MODE == PWM_CHANNEL_0_INVERTING
		copy_u8DytyCycle = 100 - copy_u8DytyCycle;
		OCR0_REG = (((u16)copy_u8DutyCycle*510)/200)-2;
		#endif
		
		#endif
		
		
		// Select Prescaler Value = 64 
	    SET_BIT(TCCR0_REG,CS00);
	    SET_BIT(TCCR0_REG,CS01);
	    CLR_BIT(TCCR0_REG,CS02);
	}
}


void PWM_voidGenerate_PWM_Channel_1A(f32 copy_f32DutyCycle, u16 copy_u16Frequency_hz)
{
	if(copy_f32DutyCycle<=100)
	{
		// under condition tick time 4 MS by setting prescaller 64
	    ICR1_u16_REG = ((1000000UL/copy_u16Frequency_hz)/4)-1;
		
		#if PWM_CHANNEL_1A_OUTPUT_MODE == PWM_CHANNEL_1A_NONINVERTING
		      OCR1A_u16_REG = ((copy_f32DutyCycle*(ICR1_u16_REG+1))/100)-1;
		#elif PWM_CHANNEL_1A_OUTPUT_MODE == PWM_CHANNEL_1A_INVERTING
		      copy_f32DytyCycle = 100 - copy_f32DytyCycle;
		      OCR1A_u16_REG = ((copy_f32DutyCycle*(ICR1_u16_REG+1))/100)-1;
		#endif


        // Select Prescaler Value = 64
	    SET_BIT(TCCR1B_REG,CS10);
	    SET_BIT(TCCR1B_REG,CS11);
	    CLR_BIT(TCCR1B_REG,CS12);		
	}
}


void PWM_voidGenerate_PWM_Channel_1B(f32 copy_f32DutyCycle, u16 copy_u16Frequency_hz)
{
	if(copy_f32DutyCycle<=100)
	{
		// under condition tick time 4 MS by setting prescaller 64
	    OCR1A_u16_REG = ((1000000UL/copy_u16Frequency_hz)/4)-1;
		
		#if PWM_CHANNEL_1B_OUTPUT_MODE == PWM_CHANNEL_1B_NONINVERTING
		      OCR1B_u16_REG = ((copy_f32DutyCycle*(OCR1A_u16_REG+1))/100)-1;
		#elif PWM_CHANNEL_1B_OUTPUT_MODE == PWM_CHANNEL_1B_INVERTING
		      copy_f32DytyCycle = 100 - copy_f32DytyCycle;
		      OCR1B_u16_REG = ((copy_f32DutyCycle*(OCR1A_u16_REG+1))/100)-1;
		#endif	


        // Select Prescaler Value = 64
	    SET_BIT(TCCR1B_REG,CS10);
	    SET_BIT(TCCR1B_REG,CS11);
	    CLR_BIT(TCCR1B_REG,CS12);			
	}
}


void PWM_voidGenerate_PWM_Channel_2(u8 copy_u8DutyCycle)
{
	if(copy_u8DutyCycle<=100)
	{
		#if PWM_CHANNEL_2_MODE == PWM_CHANNEL_2_FAST_MODE
		
		#if PWM_CHANNEL_2_OUTPUT_MODE == PWM_CHANNEL_2_NONINVERTING
		OCR2_REG = (((u16)copy_u8DutyCycle*256)/100)-1;
		#elif PWM_CHANNEL_2_OUTPUT_MODE == PWM_CHANNEL_2_INVERTING
		copy_u8DytyCycle = 100 - copy_u8DytyCycle;
		OCR2_REG = (((u16)copy_u8DutyCycle*256)/100)-1;
		#endif
		
		#elif PWM_CHANNEL_2_MODE == PWM_CHANNEL_2_PHASE_CORRECT_MODE
		#if PWM_CHANNEL_2_OUTPUT_MODE == PWM_CHANNEL_2_NONINVERTING
		OCR2_REG = (((u16)copy_u8DutyCycle*510)/200)-2;
		#elif PWM_CHANNEL_2_OUTPUT_MODE == PWM_CHANNEL_2_INVERTING
		copy_u8DytyCycle = 100 - copy_u8DytyCycle;
		OCR2_REG = (((u16)copy_u8DutyCycle*510)/200)-2;
		#endif
		
		#endif
		
		
		// Select Prescaler Value = 64 
		CLR_BIT(TCCR2_REG,CS20);
		CLR_BIT(TCCR2_REG,CS21);
		SET_BIT(TCCR2_REG,CS22);
	}
}
