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
						   
#define SSD_ENABLE_PORT			        DIO_PORTB
#define SSD_K1_ENABLE_PIN			    DIO_PIN1
#define SSD_K2_ENABLE_PIN			    DIO_PIN2


#define SSD_DATA_PORT					DIO_PORTA


/* Options FOR SSD Type:
1- SSD_COM_CATHODE
2- SSD_COM_ANNODE
*/

#define SSD_TYPE                        SSD_COM_CATHODE
#endif /* SSD_CONFIG_H_ */
