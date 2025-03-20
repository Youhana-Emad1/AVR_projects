/*
 *
 * @file GPIO_private.h
 * @author Kareem Hussein
 * @brief header file that contain GPIO private functions prototyoes, macros and declarations 
 * @date 18/08/2024      
 * @version 1.0
 *
 */
 
#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_


#define GPIO_PERIPHERAL_NUM			        8u

#define MODER_MASK					        0b11
#define MODER_PIN_ACCESS					2u

#define PUPDR_MASK					        0b11
#define PUPDR_PIN_ACCESS					2u

#define OTYPER_MASK					        0b1

#define OSPEEDR_MASK					    0b11
#define OSPEEDR_PIN_ACCESS			        2u

#define AFR_MASK					        0b1111
#define AFR_PIN_ACCESS			            4u


#endif