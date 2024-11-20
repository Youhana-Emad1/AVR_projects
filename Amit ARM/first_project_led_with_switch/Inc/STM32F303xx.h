/*
 *
 * @file STM32F303xx.h
 * @author Kareem Hussein
 * @brief header file that contain Memory mapped for STM32F303xx
 * @date 18/08/2024      
 * @version 1.0
 *
 */
 
#ifndef STM32F303XX_H_
#define STM32F303XX_H_

                   /*** Various Memories Base Addresses ***/
				   
#define FLASH_BASE_ADDRESS			0x00000000UL
#define SRAM_BASE_ADDRESS	        0x20000000UL


				   /*** AHB1 Base Addresses ***/

#define RCC_BASE_ADDRESS			0x40021000UL				   


				   /*** AHB2 Base Addresses ***/
				   
#define GPIOA_BASE_ADDRESS			0x48000000UL
#define GPIOB_BASE_ADDRESS			0x48000400UL 
#define GPIOC_BASE_ADDRESS			0x48000800UL
#define GPIOD_BASE_ADDRESS			0x48000C00UL
#define GPIOE_BASE_ADDRESS			0x48001000UL
#define GPIOF_BASE_ADDRESS			0x48001400UL
#define GPIOG_BASE_ADDRESS			0x48001800UL
#define GPIOH_BASE_ADDRESS			0x48001C00UL


                   /*** AHB3 Base Addresses ***/
                   /*** APB1 Base Addresses ***/
                   /*** APB2 Base Addresses ***/
				   
				   /*** GPIO Register Definition Struct ***/
				   
typedef struct
{
	volatile uint32_t MODER;          /*GPIO PORT Mode Register*/
	volatile uint32_t OTYPER;         /*GPIO PORT Output Type Register*/
	volatile uint32_t OSPEEDR;        /*GPIO PORT Output Speed Register*/
	volatile uint32_t PUPDR;          /*GPIO PORT Pull Up/Down Register*/
	volatile uint32_t IDR;            /*GPIO PORT Input Data Register*/
	volatile uint32_t ODR;            /*GPIO PORT Output Data Register*/
	volatile uint32_t BSRR;           /*GPIO PORT Bit Set/Reset Register*/
	volatile uint32_t LCKR;           /*GPIO PORT LockRegister*/
	volatile uint32_t AFR[2];         /*GPIO PORT Alternative Function Register*/
	volatile uint32_t BRR;            /*GPIO PORT Bit Reset Register*/
}GPIO_RegDef_t;

				   /*** RCC Register Definition Struct ***/
				   
typedef struct
{
	volatile uint32_t CR;             /*RCC Clock Control Register */
	volatile uint32_t CFGR;           /*RCC Clock Configuration Register*/
	volatile uint32_t CIR;            /*RCC Clock Interrupt Register*/
	volatile uint32_t APB2RSTR;       /*RCC APB2 Peripheral Reset Register*/
	volatile uint32_t APB1RSTR;       /*RCC APB1 Peripheral Reset Register*/
	volatile uint32_t AHBENR;         /*RCC AHB Peripheral Clock Enable Register*/
	volatile uint32_t APB2ENR;        /*RCC APB2 Peripheral Clock Enable Register*/
	volatile uint32_t APB1ENR;        /*RCC APB1 Peripheral Clock Enable Register*/
	volatile uint32_t BDCR;           /*RCC RTC Domain Control Register*/
	volatile uint32_t CSR;            /*RCC Control/Status Register*/
	volatile uint32_t AHBRSTR;        /*RCC AHB Peripheral Reset Register*/
	volatile uint32_t CFGR2;          /*RCC Clock Configuration Register 2*/
	volatile uint32_t CFGR3;          /*RCC Clock Configuration Register 3*/
}RCC_RegDef_t;

                   /*** GPIO Peripherals Definitions ***/
				   
#define GPIOA			((GPIO_RegDef_t*)GPIOA_BASE_ADDRESS)
#define GPIOB			((GPIO_RegDef_t*)GPIOB_BASE_ADDRESS)
#define GPIOC			((GPIO_RegDef_t*)GPIOC_BASE_ADDRESS)
#define GPIOD			((GPIO_RegDef_t*)GPIOD_BASE_ADDRESS)
#define GPIOE			((GPIO_RegDef_t*)GPIOE_BASE_ADDRESS)
#define GPIOF			((GPIO_RegDef_t*)GPIOF_BASE_ADDRESS)
#define GPIOG			((GPIO_RegDef_t*)GPIOG_BASE_ADDRESS)
#define GPIOH			((GPIO_RegDef_t*)GPIOH_BASE_ADDRESS)


				   /*** RCC Peripheral Definitions ***/

#define RCC			    ((RCC_RegDef_t*)RCC_BASE_ADDRESS)

	   
#endif