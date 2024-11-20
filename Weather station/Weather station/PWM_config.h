/******************************************************************************
 *                                                                            *
 *************************  SWC     : PWM_config      *************************
 *************************  Date    : 14/01/2024      *************************
 *************************  Author  : kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/

#ifndef PWM_CONFIG_H_
#define PWM_CONFIG_H_


                                 /* PWM_CHANNEL_0 CONFIGURATIONS */
/* Options FOR PWM0 Mode:
1- PWM_CHANNEL_0_FAST_MODE
2- PWM_CHANNEL_0_PHASE_CORRECT_MODE
*/								 
#define PWM_CHANNEL_0_MODE			        PWM_CHANNEL_0_FAST_MODE

/* Options FOR PWM0 OUTPUT Mode:
1- PWM_CHANNEL_0_NONINVERTING
2- PWM_CHANNEL_0_INVERTING
*/
#define PWM_CHANNEL_0_OUTPUT_MODE			PWM_CHANNEL_0_NONINVERTING


                                 /* PWM_CHANNEL_1A CONFIGURATIONS */
/* Options FOR PWM1A OUTPUT Mode:
1- PWM_CHANNEL_1A_NONINVERTING
2- PWM_CHANNEL_1A_INVERTING
*/
#define PWM_CHANNEL_1A_OUTPUT_MODE			PWM_CHANNEL_1A_NONINVERTING


                                 /* PWM_CHANNEL_1B CONFIGURATIONS */
/* Options FOR PWM1B OUTPUT Mode:
1- PWM_CHANNEL_1B_NONINVERTING
2- PWM_CHANNEL_1B_INVERTING
*/
#define PWM_CHANNEL_1B_OUTPUT_MODE			PWM_CHANNEL_1B_NONINVERTING


                                 /* PWM_CHANNEL_2 CONFIGURATIONS */
/* Options FOR PWM2 Mode:
1- PWM_CHANNEL_2_FAST_MODE
2- PWM_CHANNEL_2_PHASE_CORRECT_MODE
*/
#define PWM_CHANNEL_2_MODE			        PWM_CHANNEL_2_FAST_MODE

/* Options FOR PWM2 OUTPUT Mode:
1- PWM_CHANNEL_2_NONINVERTING
2- PWM_CHANNEL_2_INVERTING
*/
#define PWM_CHANNEL_2_OUTPUT_MODE			PWM_CHANNEL_2_NONINVERTING


#endif /* PWM_CONFIG_H_ */
