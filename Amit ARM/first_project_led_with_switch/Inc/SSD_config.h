/******************************************************************************
 *                                                                            *
 *************************  SWC     : SSD_config      *************************
 *************************  Date    : 25/02/2024      *************************
 *************************  Author  : Kareem Hussein  *************************
 *************************  Version : 1.0             *************************
 *                                                                            *
 ******************************************************************************/

#ifndef SSD_CONFIG_H_
#define SSD_CONFIG_H_


                           /* Macros for SSD decoder Pins Configurations */
						   
#define SSD_ENABLE_PORT			        GPIO_PORTC
#define SSD_K1_ENABLE_PIN			    GPIO_PIN2
#define SSD_K2_ENABLE_PIN			    GPIO_PIN3


#define SSD_A_PORT					GPIO_PORTC
#define SSD_A_PIN				    GPIO_PIN10

#define SSD_B_PORT					GPIO_PORTC
#define SSD_B_PIN				    GPIO_PIN12

#define SSD_C_PORT					GPIO_PORTF
#define SSD_C_PIN				    GPIO_PIN6

#define SSD_D_PORT					GPIO_PORTF
#define SSD_D_PIN				    GPIO_PIN7

#define SSD_E_PORT					GPIO_PORTA
#define SSD_E_PIN				    GPIO_PIN13

#define SSD_F_PORT					GPIO_PORTA
#define SSD_F_PIN				    GPIO_PIN14

#define SSD_G_PORT					GPIO_PORTA
#define SSD_G_PIN				    GPIO_PIN15

/* Options FOR SSD Type:
1- SSD_COM_CATHODE
2- SSD_COM_ANNODE
*/

#define SSD_TYPE                        SSD_COM_CATHODE
#endif /* SSD_CONFIG_H_ */
