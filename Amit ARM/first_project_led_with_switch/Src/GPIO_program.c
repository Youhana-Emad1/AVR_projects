/*
 *
 * @file GPIO_program.c
 * @author Kareem Hussein
 * @brief main source file that contain GPIO functions implementation
 * @date 18/08/2024      
 * @version 1.0
 *
 */
 
#include <stdint.h>

/* UTILES_LIB */
#include "STM32F303xx.h"
#include "ERROR_TYPE.h"

/* MCAL */
#include "GPIO_interface.h"
#include "GPIO_private.h"


static GPIO_RegDef_t* PRV_arrGPIO_Ports[GPIO_PERIPHERAL_NUM] = {GPIOA, GPIOB, GPIOC, GPIOD, GPIOE, GPIOF, GPIOG, GPIOH};

/*
 * @fn GPIO_u8InitPin
 * @brief the function initializes the GPIO pin according to the input configurations
 * @param[in] copy_pStrPinConfig : the initialization value of the pin
 * @retVal ErrorState
 */
 uint8_t GPIO_u8InitPin(const GPIO_pinConfig_t* copy_pStrPinConfig)
{
	uint8_t local_u8ErrorState = OK;
	if(copy_pStrPinConfig != NULL)
	{
		if((copy_pStrPinConfig->portId <= GPIO_PORTH)&&(copy_pStrPinConfig->pinId <= GPIO_PIN15))
		{
			/* Select GPIO Mode: Input, Output, Analog, Alternate Function */
			// Clear the Mode Bits
			PRV_arrGPIO_Ports[copy_pStrPinConfig->portId]->MODER &= (~(MODER_MASK << (copy_pStrPinConfig->pinId) * MODER_PIN_ACCESS));
			PRV_arrGPIO_Ports[copy_pStrPinConfig->portId]->MODER |= (copy_pStrPinConfig->pinMode) << ((copy_pStrPinConfig->pinId) * MODER_PIN_ACCESS);
			
			/* Select GPIO Pull State: No Pull, Pull Up, Pull Down */
			/* Clear the Pull Bits */
			PRV_arrGPIO_Ports[copy_pStrPinConfig->portId]->PUPDR &= (~(PUPDR_MASK << (copy_pStrPinConfig->pinId) * PUPDR_PIN_ACCESS));
			PRV_arrGPIO_Ports[copy_pStrPinConfig->portId]->PUPDR |= ((copy_pStrPinConfig->pinPullType) << (copy_pStrPinConfig->pinId) * PUPDR_PIN_ACCESS);
			
			/* Select Output Type & Output Speed in case of GPIO Output or Alternate Function */
			if(((copy_pStrPinConfig->pinMode) == GPIO_OUTPUT) || ((copy_pStrPinConfig->pinMode) == GPIO_ALTERNATE_FUNCTION))
			{
				/* Select Output Type: Push Pull, Open Drain */
				PRV_arrGPIO_Ports[copy_pStrPinConfig->portId]->OTYPER &= (~(OTYPER_MASK << copy_pStrPinConfig->pinId));
				PRV_arrGPIO_Ports[copy_pStrPinConfig->portId]->OTYPER |= ((copy_pStrPinConfig->pinOutputType) << (copy_pStrPinConfig->pinId));

				/* Select Output Speed: Low, Medium, High */
				PRV_arrGPIO_Ports[copy_pStrPinConfig->portId]->OSPEEDR &= (~(OSPEEDR_MASK << (copy_pStrPinConfig->pinId) * OSPEEDR_PIN_ACCESS));
				PRV_arrGPIO_Ports[copy_pStrPinConfig->portId]->OSPEEDR |= ((copy_pStrPinConfig->pinSpeed) << (copy_pStrPinConfig->pinId) * OSPEEDR_PIN_ACCESS);

				/* Select the Pin Alternative Function */
				if((copy_pStrPinConfig->pinMode) == GPIO_ALTERNATE_FUNCTION)
				{
					PRV_arrGPIO_Ports[copy_pStrPinConfig->portId]->AFR[(copy_pStrPinConfig->pinId) / 8u] &= (~(AFR_MASK << ((copy_pStrPinConfig->pinId) % 8) * AFR_PIN_ACCESS));
					PRV_arrGPIO_Ports[copy_pStrPinConfig->portId]->AFR[(copy_pStrPinConfig->pinId) / 8u] |= ((copy_pStrPinConfig->pinAltFunc) << ((copy_pStrPinConfig->pinId) % 8) * AFR_PIN_ACCESS);
				}
			}
		}
		else
		{
			local_u8ErrorState = NOK;
		}
		}
	else
	{
		local_u8ErrorState = NULL_PTR_ERR;
	}
	return local_u8ErrorState;
}


/*
 * @fn GPIO_u8SetPinValue
 * @brief the function outputs a certain value on GPIO output pin
 * @param[in] copy_enuPortId : port number, get options @GPIO_portId_t enum
 * @param[in] copy_enuPinId : pin number, get options @GPIO_pinId_t enum
 * @param[in] copy_enuPinValue: the output value, get options @GPIO_pinValue_t enum
 * @retVal ErrorState
 */
uint8_t GPIO_u8SetPinValue(GPIO_portId_t copy_enuPortId, GPIO_pinId_t copy_enuPinId, GPIO_pinValue_t copy_enuPinValue)
{
	uint8_t local_u8ErrorState = OK;
	if((copy_enuPortId <= GPIO_PORTH)&&(copy_enuPinId <= GPIO_PIN15))
	{
		if(copy_enuPinValue == GPIO_PIN_LOW)
		{
			PRV_arrGPIO_Ports[copy_enuPortId]->ODR &= (~(0b1 << copy_enuPinId));
			/* PRV_arrGPIO_Ports[copy_enuPortId]->BSRR = (0b1 << (16 + copy_enuPinId)); */
			/* PRV_arrGPIO_Ports[copy_enuPortId]->BRR  = (0b1 << (copy_enuPinId)); */
		}
		else if(copy_enuPinValue == GPIO_PIN_HIGH)
		{
			PRV_arrGPIO_Ports[copy_enuPortId]->ODR |= (0b1 << copy_enuPinId);
			/* PRV_arrGPIO_Ports[copy_enuPortId]->BSRR = (0b1 << copy_enuPinId); */
		}
		else
		{
			local_u8ErrorState = NOK;
		}
	}
	else
	{
		local_u8ErrorState = NOK;
	}
	return local_u8ErrorState;
}


/*
 * @fn GPIO_u8TogglePinValue
 * @brief the function toggle the value of GPIO output pin
 * @param[in] copy_enuPortId : port number, get options @GPIO_portId_t enum
 * @param[in] copy_enuPinId : pin number, get options @GPIO_pinId_t enum
 * @retVal ErrorState
 */
uint8_t GPIO_u8TogglePinValue(GPIO_portId_t copy_enuPortId, GPIO_pinId_t copy_enuPinId)
{
	uint8_t local_u8ErrorState = OK;
	if((copy_enuPortId <= GPIO_PORTH)&&(copy_enuPinId <= GPIO_PIN15))
	{
		PRV_arrGPIO_Ports[copy_enuPortId]->ODR ^= (0b1 << copy_enuPinId);
	}
	else
	{
		local_u8ErrorState = NOK;
	}
	return local_u8ErrorState;
}


/*
 * @fn GPIO_u8GetPinValue
 * @brief the function read a certain value on GPIO input pin
 * @param[in] copy_enuPortId : port number, get options @GPIO_portId_t enum
 * @param[in] copy_enuPinId : pin number, get options @GPIO_pinId_t enum
 * @param[out] copy_PEnuPinValue: the pin value
 * @retVal ErrorState
 */
uint8_t GPIO_u8GetPinValue(GPIO_portId_t copy_enuPortId, GPIO_pinId_t copy_enuPinId, GPIO_pinValue_t* copy_PEnuPinValue)
{
	uint8_t local_u8ErrorState = OK;
	if(copy_PEnuPinValue != NULL)
	{
		if((copy_enuPortId <= GPIO_PORTH)&&(copy_enuPinId <= GPIO_PIN15))
		{
			*copy_PEnuPinValue = ((PRV_arrGPIO_Ports[copy_enuPortId]->IDR) >> copy_enuPinId) & 0b1;
		}
		else
		{
			local_u8ErrorState = NOK;
		}
	}
	else
	{
		local_u8ErrorState = NULL_PTR_ERR;
	}
	return local_u8ErrorState;
}
