/******************************************************************************
 *                                                                            *
 *************************  SWC     : PWM_interface   *************************
 *************************  Date    : 14/01/2024      *************************
 *************************  Author  : kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/

#ifndef PWM_INTERFACE_H_
#define PWM_INTERFACE_H_


                       /*************** APIS PROTOTYPES ***************/
					   
void PWM_voidInitChannel_0          (void);
void PWM_voidInitChannel_1A         (void);
void PWM_voidInitChannel_1B         (void);
void PWM_voidInitChannel_2          (void);
void PWM_voidGenerate_PWM_Channel_0 (u8  copy_u8DutyCycle);
void PWM_voidGenerate_PWM_Channel_1A(f32 copy_f32DutyCycle, u16 copy_u16Frequency_hz);
void PWM_voidGenerate_PWM_Channel_1B(f32 copy_f32DutyCycle, u16 copy_u16Frequency_hz);
void PWM_voidGenerate_PWM_Channel_2 (u8  copy_u8DutyCycle);


#endif /* PWM_INTERFACE_H_ */
