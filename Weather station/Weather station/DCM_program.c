/******************************************************************************
 *                                                                            *
 *************************  SWC     : DCM_program     *************************
 *************************  Date    : 25/02/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/


/* UTILES_LIB */
#include "STD_TYPES.h"
#include "BIT_MATH.h"

/* MCAL */
#include "DIO_interface.h"
#include "PWM_interface.h"

/* HAL */
#include "DCM_interface.h"
#include "DCM_config.h"


void DCM_voidInit(u8 copy_u8MotorId)
{
	/* Initializ H-Bridge As Output Pins depend on motor id*/
	switch(copy_u8MotorId)
	{
	case DCM_MOTOR_A:
		DIO_voidSetPinDirection(DCM_MOTOR_A_IN1_PORT, DCM_MOTOR_A_IN1_PIN, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection(DCM_MOTOR_A_IN2_PORT, DCM_MOTOR_A_IN2_PIN, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection(DCM_MOTOR_A_ENABLE_PORT, DCM_MOTOR_A_ENABLE_PIN, DIO_PIN_OUTPUT);
		break;

	case DCM_MOTOR_B:
		DIO_voidSetPinDirection(DCM_MOTOR_B_IN1_PORT, DCM_MOTOR_B_IN1_PIN, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection(DCM_MOTOR_B_IN2_PORT, DCM_MOTOR_B_IN2_PIN, DIO_PIN_OUTPUT);
		DIO_voidSetPinDirection(DCM_MOTOR_B_ENABLE_PORT, DCM_MOTOR_B_ENABLE_PIN, DIO_PIN_OUTPUT);
		break;

	}
}


void DCM_voidOn(u8 copy_u8MotorId, u8 Copy_u8MotorDirection)
{
	/* Turn DC motor on using H-Bridge Pins depend on Copy_u8Direction*/
	switch(copy_u8MotorId)
	{
	case DCM_MOTOR_A:
		switch(Copy_u8MotorDirection)
		{
		case DCM_CLOCK_WISE:
			DIO_voidSetPinValue(DCM_MOTOR_A_IN1_PORT, DCM_MOTOR_A_IN1_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(DCM_MOTOR_A_IN2_PORT, DCM_MOTOR_A_IN2_PIN, DIO_PIN_LOW);
			break;

		case DCM_COUNTER_CLOCK_WISE:
			DIO_voidSetPinValue(DCM_MOTOR_A_IN1_PORT, DCM_MOTOR_A_IN1_PIN, DIO_PIN_LOW);
			DIO_voidSetPinValue(DCM_MOTOR_A_IN2_PORT, DCM_MOTOR_A_IN2_PIN, DIO_PIN_HIGH);
			break;
		}
		DIO_voidSetPinValue(DCM_MOTOR_A_ENABLE_PORT, DCM_MOTOR_A_ENABLE_PIN, DIO_PIN_HIGH);
		break;

		case DCM_MOTOR_B:
			switch(Copy_u8MotorDirection)
			{
			case DCM_CLOCK_WISE:
				DIO_voidSetPinValue(DCM_MOTOR_B_IN1_PORT, DCM_MOTOR_B_IN1_PIN, DIO_PIN_HIGH);
				DIO_voidSetPinValue(DCM_MOTOR_B_IN2_PORT, DCM_MOTOR_B_IN2_PIN, DIO_PIN_LOW);
				break;

			case DCM_COUNTER_CLOCK_WISE:
				DIO_voidSetPinValue(DCM_MOTOR_B_IN1_PORT, DCM_MOTOR_B_IN1_PIN, DIO_PIN_LOW);
				DIO_voidSetPinValue(DCM_MOTOR_B_IN2_PORT, DCM_MOTOR_B_IN2_PIN, DIO_PIN_HIGH);
				break;
			}
			DIO_voidSetPinValue(DCM_MOTOR_B_ENABLE_PORT, DCM_MOTOR_B_ENABLE_PIN, DIO_PIN_HIGH);
			break;
	}
}


void DCM_voidControlSpeed(u8 copy_u8MotorId, u8 Copy_u8MotorDirection, u8 Copy_u8Speed)
{
	/* Turn DC motor on with Controlling desired(motorId) DC motor speed using PWM0 by setting Duty Cycle and turn it on using H-Bridge
	 By Setting Dir and Enable pins depend on motorDirection*/
	switch(copy_u8MotorId)
	{
	    case DCM_MOTOR_A:
		switch(Copy_u8MotorDirection)
		{
		case DCM_CLOCK_WISE:
			DIO_voidSetPinValue(DCM_MOTOR_A_IN1_PORT, DCM_MOTOR_A_IN1_PIN, DIO_PIN_HIGH);
			DIO_voidSetPinValue(DCM_MOTOR_A_IN2_PORT, DCM_MOTOR_A_IN2_PIN, DIO_PIN_LOW);
			break;

		case DCM_COUNTER_CLOCK_WISE:
			DIO_voidSetPinValue(DCM_MOTOR_A_IN1_PORT, DCM_MOTOR_A_IN1_PIN, DIO_PIN_LOW);
			DIO_voidSetPinValue(DCM_MOTOR_A_IN2_PORT, DCM_MOTOR_A_IN2_PIN, DIO_PIN_HIGH);
			break;
		}
		PWM_voidInitChannel_1B();
		PWM_voidGenerate_PWM_Channel_1B(Copy_u8Speed, 1000);
		break;

		case DCM_MOTOR_B:
			switch(Copy_u8MotorDirection)
			{
			case DCM_CLOCK_WISE:
				DIO_voidSetPinValue(DCM_MOTOR_B_IN1_PORT, DCM_MOTOR_B_IN1_PIN, DIO_PIN_HIGH);
				DIO_voidSetPinValue(DCM_MOTOR_B_IN2_PORT, DCM_MOTOR_B_IN2_PIN, DIO_PIN_LOW);
				break;

			case DCM_COUNTER_CLOCK_WISE:
				DIO_voidSetPinValue(DCM_MOTOR_B_IN1_PORT, DCM_MOTOR_B_IN1_PIN, DIO_PIN_LOW);
				DIO_voidSetPinValue(DCM_MOTOR_B_IN2_PORT, DCM_MOTOR_B_IN2_PIN, DIO_PIN_HIGH);
				break;
			}
			PWM_voidInitChannel_1A();
			PWM_voidGenerate_PWM_Channel_1A(Copy_u8Speed, 1000);
			break;
	}
}


void DCM_voidOff(copy_u8MotorId)
{
	switch(copy_u8MotorId)
	{
	    case DCM_MOTOR_A:
	    DIO_voidSetPinValue(DCM_MOTOR_A_ENABLE_PORT, DCM_MOTOR_A_ENABLE_PIN, DIO_PIN_LOW);
		break;

	    case DCM_MOTOR_B:
	   	DIO_voidSetPinValue(DCM_MOTOR_B_ENABLE_PORT, DCM_MOTOR_B_ENABLE_PIN, DIO_PIN_LOW);
	    break;
	}
}


