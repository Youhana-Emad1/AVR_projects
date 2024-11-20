/******************************************************************************
 *                                                                            *
 *************************  SWC     : DCM_config      *************************
 *************************  Date    : 25/02/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/

#ifndef DCM_CONFIG_H_
#define DCM_CONFIG_H_


                           /* Macros for H-Bridge Pins Configurations */

#define DCM_MOTOR_A_ENABLE_PORT			DIO_PORTB
#define DCM_MOTOR_A_ENABLE_PIN			DIO_PIN3

#define DCM_MOTOR_A_IN1_PORT			DIO_PORTC
#define DCM_MOTOR_A_IN1_PIN  			DIO_PIN3

#define DCM_MOTOR_A_IN2_PORT			DIO_PORTC
#define DCM_MOTOR_A_IN2_PIN  			DIO_PIN4


#define DCM_MOTOR_B_ENABLE_PORT			DIO_PORTD
#define DCM_MOTOR_B_ENABLE_PIN			DIO_PIN5

#define DCM_MOTOR_B_IN1_PORT			DIO_PORTC
#define DCM_MOTOR_B_IN1_PIN  			DIO_PIN5

#define DCM_MOTOR_B_IN2_PORT			DIO_PORTC
#define DCM_MOTOR_B_IN2_PIN  			DIO_PIN6


#endif /* DCM_CONFIG_H_ */
