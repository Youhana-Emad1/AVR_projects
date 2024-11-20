/*
 *
 * @file RCC_program.c
 * @author Kareem Hussein
 * @brief main source file that contain RCC functions implementation
 * @date 18/08/2024      
 * @version 1.0
 *
 */
 
#include <stdint.h>

/* UTILES_LIB */
#include "STM32F303xx.h"
#include "ERROR_TYPE.h"
#include "BIT_MATH.h"

/* MCAL */
#include "RCC_interface.h"
#include "RCC_private.h"


void RCC_voidSetClockStatus(RCC_clkType_t copy_tClockType, RCC_clkStatus_t copy_tClockStatus)
{
	switch(copy_tClockType)
	{
	case RCC_CLK_HSI:
		switch(copy_tClockStatus)
		{
		case RCC_CLK_ON:
			SET_BIT(RCC->CR, 0);
			while(0 == GET_BIT(RCC->CR, 1));
			break;

		case RCC_CLK_OFF:
			CLR_BIT(RCC->CR, 0);
			break;
		}
		break;

		case RCC_CLK_HSE:
			switch(copy_tClockStatus)
			{
			case RCC_CLK_ON:
				SET_BIT(RCC->CR, 16);
				while(0 == GET_BIT(RCC->CR, 17));
				break;

			case RCC_CLK_OFF:
				CLR_BIT(RCC->CR, 16);
				break;
			}
			break;

			case RCC_CLK_PLL:
				switch(copy_tClockStatus)
				{
				case RCC_CLK_ON:
					SET_BIT(RCC->CR, 24);
					while(0 == GET_BIT(RCC->CR, 25));
					break;

				case RCC_CLK_OFF:
					CLR_BIT(RCC->CR, 24);
					break;
				}
				break;
	}
}


void RCC_voidSetSystemClock(RCC_clkType_t copy_tClockType)
{
	switch(copy_tClockType)
	{
	case RCC_CLK_HSI:
		CLR_BIT(RCC->CFGR, 0);
		CLR_BIT(RCC->CFGR, 1);
		break;

	case RCC_CLK_HSE:
		SET_BIT(RCC->CFGR, 0);
		CLR_BIT(RCC->CFGR, 1);
		break;

	case RCC_CLK_PLL:
		CLR_BIT(RCC->CFGR, 0);
		SET_BIT(RCC->CFGR, 1);
		break;
	}
}


void RCC_voidSet_HSE_configurations(RCC_HSE_prescaler_t copy_tPrescaler)
{
	switch(copy_tPrescaler)
	{
	case RCC_HSE_BY1:
		CLR_BIT(RCC->CFGR, 17);
		break;

	case RCC_HSE_BY2:
		SET_BIT(RCC->CFGR, 17);
		break;
	}
}


void RCC_voidSet_PLL_configurations(RCC_PLL_source_t copy_tSource, RCC_PLL_mulFactor_t copy_tMultiplicationFactor)
{
	switch(copy_tSource)
	{
	case RCC_PLL_SOURCE_HSI:
		CLR_BIT(RCC->CFGR, 16);
		break;

	case RCC_PLL_SOURCE_HSE:
		SET_BIT(RCC->CFGR, 16);
		break;
	}

	switch(copy_tMultiplicationFactor)
	{
	case RCC_PLL_MUL_2:
		CLR_BIT(RCC->CFGR, 18);
		CLR_BIT(RCC->CFGR, 19);
		CLR_BIT(RCC->CFGR, 20);
		CLR_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_3:
		SET_BIT(RCC->CFGR, 18);
		CLR_BIT(RCC->CFGR, 19);
		CLR_BIT(RCC->CFGR, 20);
		CLR_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_4:
		CLR_BIT(RCC->CFGR, 18);
		SET_BIT(RCC->CFGR, 19);
		CLR_BIT(RCC->CFGR, 20);
		CLR_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_5:
		SET_BIT(RCC->CFGR, 18);
		SET_BIT(RCC->CFGR, 19);
		CLR_BIT(RCC->CFGR, 20);
		CLR_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_6:
		CLR_BIT(RCC->CFGR, 18);
		CLR_BIT(RCC->CFGR, 19);
		SET_BIT(RCC->CFGR, 20);
		CLR_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_7:
		SET_BIT(RCC->CFGR, 18);
		CLR_BIT(RCC->CFGR, 19);
		SET_BIT(RCC->CFGR, 20);
		CLR_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_8:
		CLR_BIT(RCC->CFGR, 18);
		SET_BIT(RCC->CFGR, 19);
		SET_BIT(RCC->CFGR, 20);
		CLR_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_9:
		SET_BIT(RCC->CFGR, 18);
		SET_BIT(RCC->CFGR, 19);
		SET_BIT(RCC->CFGR, 20);
		CLR_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_10:
		CLR_BIT(RCC->CFGR, 18);
		CLR_BIT(RCC->CFGR, 19);
		CLR_BIT(RCC->CFGR, 20);
		SET_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_11:
		SET_BIT(RCC->CFGR, 18);
		CLR_BIT(RCC->CFGR, 19);
		CLR_BIT(RCC->CFGR, 20);
		SET_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_12:
		CLR_BIT(RCC->CFGR, 18);
		SET_BIT(RCC->CFGR, 19);
		CLR_BIT(RCC->CFGR, 20);
		SET_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_13:
		SET_BIT(RCC->CFGR, 18);
		SET_BIT(RCC->CFGR, 19);
		CLR_BIT(RCC->CFGR, 20);
		SET_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_14:
		CLR_BIT(RCC->CFGR, 18);
		CLR_BIT(RCC->CFGR, 19);
		SET_BIT(RCC->CFGR, 20);
		SET_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_15:
		SET_BIT(RCC->CFGR, 18);
		CLR_BIT(RCC->CFGR, 19);
		SET_BIT(RCC->CFGR, 20);
		SET_BIT(RCC->CFGR, 21);
		break;

	case RCC_PLL_MUL_16:
		CLR_BIT(RCC->CFGR, 18);
		SET_BIT(RCC->CFGR, 19);
		SET_BIT(RCC->CFGR, 20);
		SET_BIT(RCC->CFGR, 21);
		break;
	}
}


void RCC_voidSet_APB2_clockPrescaler(RCC_APB2_prescaler_t copy_tPrescaler)
{
	switch(copy_tPrescaler)
	{
		case RCC_APB2_HCLK_BY1:
		CLR_BIT(RCC->CFGR, 11);
		CLR_BIT(RCC->CFGR, 12);
		CLR_BIT(RCC->CFGR, 13);
		break;
		
		case RCC_APB2_HCLK_BY2:
		CLR_BIT(RCC->CFGR, 11);
		CLR_BIT(RCC->CFGR, 12);
		SET_BIT(RCC->CFGR, 13);
		break;
		
		case RCC_APB2_HCLK_BY4:
		SET_BIT(RCC->CFGR, 11);
		CLR_BIT(RCC->CFGR, 12);
		SET_BIT(RCC->CFGR, 13);
		break;
		
		case RCC_APB2_HCLK_BY8:
		CLR_BIT(RCC->CFGR, 11);
		SET_BIT(RCC->CFGR, 12);
		SET_BIT(RCC->CFGR, 13);
		break;
		
		case RCC_APB2_HCLK_BY16:
		SET_BIT(RCC->CFGR, 11);
		SET_BIT(RCC->CFGR, 12);
		SET_BIT(RCC->CFGR, 13);
		break;
	}
}


void RCC_voidSet_APB1_clockPrescaler(RCC_APB1_prescaler_t copy_tPrescaler)
{
	switch(copy_tPrescaler)
	{
		case RCC_APB1_HCLK_BY1:
		CLR_BIT(RCC->CFGR, 8);
		CLR_BIT(RCC->CFGR, 9);
		CLR_BIT(RCC->CFGR, 10);
		break;
		
		case RCC_APB1_HCLK_BY2:
		CLR_BIT(RCC->CFGR, 8);
		CLR_BIT(RCC->CFGR, 9);
		SET_BIT(RCC->CFGR, 10);
		break;
		
		case RCC_APB1_HCLK_BY4:
		SET_BIT(RCC->CFGR, 8);
		CLR_BIT(RCC->CFGR, 9);
		SET_BIT(RCC->CFGR, 10);
		break;
		
		case RCC_APB1_HCLK_BY8:
		CLR_BIT(RCC->CFGR, 8);
		SET_BIT(RCC->CFGR, 9);
		SET_BIT(RCC->CFGR, 10);
		break;
		
		case RCC_APB1_HCLK_BY16:
		SET_BIT(RCC->CFGR, 8);
		SET_BIT(RCC->CFGR, 9);
		SET_BIT(RCC->CFGR, 10);
		break;
	}
}


void RCC_voidSet_AHB_clockPrescaler(RCC_AHB_prescaler_t copy_tPrescaler)
{
	switch(copy_tPrescaler)
	{
		case RCC_AHB_SYSCLK_BY1:
		CLR_BIT(RCC->CFGR, 4);
		CLR_BIT(RCC->CFGR, 5);
		CLR_BIT(RCC->CFGR, 6);
		CLR_BIT(RCC->CFGR, 7);
		break;
		
		case RCC_AHB_SYSCLK_BY2:
		CLR_BIT(RCC->CFGR, 4);
		CLR_BIT(RCC->CFGR, 5);
		CLR_BIT(RCC->CFGR, 6);
		SET_BIT(RCC->CFGR, 7);
		break;
		
		case RCC_AHB_SYSCLK_BY4:
		SET_BIT(RCC->CFGR, 4);
		CLR_BIT(RCC->CFGR, 5);
		CLR_BIT(RCC->CFGR, 6);
		SET_BIT(RCC->CFGR, 7);
		break;
		
		case RCC_AHB_SYSCLK_BY8:
		CLR_BIT(RCC->CFGR, 4);
		SET_BIT(RCC->CFGR, 5);
		CLR_BIT(RCC->CFGR, 6);
		SET_BIT(RCC->CFGR, 7);
		break;
		
		case RCC_AHB_SYSCLK_BY16:
		SET_BIT(RCC->CFGR, 4);
		SET_BIT(RCC->CFGR, 5);
		CLR_BIT(RCC->CFGR, 6);
		SET_BIT(RCC->CFGR, 7);
		break;
		
		case RCC_AHB_SYSCLK_BY64:
		CLR_BIT(RCC->CFGR, 4);
		CLR_BIT(RCC->CFGR, 5);
		SET_BIT(RCC->CFGR, 6);
		SET_BIT(RCC->CFGR, 7);
		break;
		
		case RCC_AHB_SYSCLK_BY128:
		SET_BIT(RCC->CFGR, 4);
		CLR_BIT(RCC->CFGR, 5);
		SET_BIT(RCC->CFGR, 6);
		SET_BIT(RCC->CFGR, 7);
		break;
		
		case RCC_AHB_SYSCLK_BY256:
		CLR_BIT(RCC->CFGR, 4);
		SET_BIT(RCC->CFGR, 5);
		SET_BIT(RCC->CFGR, 6);
		SET_BIT(RCC->CFGR, 7);
		break;
		
		case RCC_AHB_SYSCLK_BY512:
		SET_BIT(RCC->CFGR, 4);
		SET_BIT(RCC->CFGR, 5);
		SET_BIT(RCC->CFGR, 6);
		SET_BIT(RCC->CFGR, 7);
		break;
	}
}


void RCC_voidEnable_AHB_clock(RCC_AHB_peripherals_t copy_tPeripheral)
{
	switch(copy_tPeripheral)
	{
		case RCC_AHB_DMA1EN:
		SET_BIT(RCC->AHBENR, 0);
		break;
		
		case RCC_AHB_DMA2EN:
		SET_BIT(RCC->AHBENR, 1);
		break;
		
		case RCC_AHB_SRAMEN:
		SET_BIT(RCC->AHBENR, 2);
		break;
		
		case RCC_AHB_FLITFEN:
		SET_BIT(RCC->AHBENR, 4);
		break;
		
		case RCC_AHB_FMCEN:
		SET_BIT(RCC->AHBENR, 5);
		break;
		
		case RCC_AHB_CRCEN:
		SET_BIT(RCC->AHBENR, 6);
		break;
		
		case RCC_AHB_IOPHEN:
		SET_BIT(RCC->AHBENR, 16);
		break;
		
		case RCC_AHB_IOPAEN:
		SET_BIT(RCC->AHBENR, 17);
		break;
		
		case RCC_AHB_IOPBEN:
		SET_BIT(RCC->AHBENR, 18);
		break;
		
		case RCC_AHB_IOPCEN:
		SET_BIT(RCC->AHBENR, 19);
		break;
		
		case RCC_AHB_IOPDEN:
		SET_BIT(RCC->AHBENR, 20);
		break;
		
		case RCC_AHB_IOPEEN:
		SET_BIT(RCC->AHBENR, 21);
		break;
		
		case RCC_AHB_IOPFEN:
		SET_BIT(RCC->AHBENR, 22);
		break;
		
		case RCC_AHB_IOPGEN:
		SET_BIT(RCC->AHBENR, 23);
		break;
		
		case RCC_AHB_TSCEN:
		SET_BIT(RCC->AHBENR, 24);
		break;
		
		case RCC_AHB_ADC12EN:
		SET_BIT(RCC->AHBENR, 28);
		break;
		
		case RCC_AHB_ADC34EN:
		SET_BIT(RCC->AHBENR, 29);
		break;
	}
}


void RCC_voidDisable_AHB_clock(RCC_AHB_peripherals_t copy_tPeripheral)
{
	switch(copy_tPeripheral)
	{
		case RCC_AHB_DMA1EN:
		CLR_BIT(RCC->AHBENR, 0);
		break;
		
		case RCC_AHB_DMA2EN:
		CLR_BIT(RCC->AHBENR, 1);
		break;
		
		case RCC_AHB_SRAMEN:
		CLR_BIT(RCC->AHBENR, 2);
		break;
		
		case RCC_AHB_FLITFEN:
		CLR_BIT(RCC->AHBENR, 4);
		break;
		
		case RCC_AHB_FMCEN:
		CLR_BIT(RCC->AHBENR, 5);
		break;
		
		case RCC_AHB_CRCEN:
		CLR_BIT(RCC->AHBENR, 6);
		break;
		
		case RCC_AHB_IOPHEN:
		CLR_BIT(RCC->AHBENR, 16);
		break;
		
		case RCC_AHB_IOPAEN:
		CLR_BIT(RCC->AHBENR, 17);
		break;
		
		case RCC_AHB_IOPBEN:
		CLR_BIT(RCC->AHBENR, 18);
		break;
		
		case RCC_AHB_IOPCEN:
		CLR_BIT(RCC->AHBENR, 19);
		break;
		
		case RCC_AHB_IOPDEN:
		CLR_BIT(RCC->AHBENR, 20);
		break;
		
		case RCC_AHB_IOPEEN:
		CLR_BIT(RCC->AHBENR, 21);
		break;
		
		case RCC_AHB_IOPFEN:
		CLR_BIT(RCC->AHBENR, 22);
		break;
		
		case RCC_AHB_IOPGEN:
		CLR_BIT(RCC->AHBENR, 23);
		break;
		
		case RCC_AHB_TSCEN:
		CLR_BIT(RCC->AHBENR, 24);
		break;
		
		case RCC_AHB_ADC12EN:
		CLR_BIT(RCC->AHBENR, 28);
		break;
		
		case RCC_AHB_ADC34EN:
		CLR_BIT(RCC->AHBENR, 29);
		break;
	}
}


void RCC_voidEnable_APB1_clock(RCC_APB1_peripherals_t copy_tPeripheral)
{
	switch(copy_tPeripheral)
	{
		case RCC_APB1_TIM2EN:
		SET_BIT(RCC->APB1ENR, 0);
		break;
		
		case RCC_APB1_TIM3EN:
		SET_BIT(RCC->APB1ENR, 1);
		break;
		
		case RCC_APB1_TIM4EN:
		SET_BIT(RCC->APB1ENR, 2);
		break;
		
		case RCC_APB1_TIM6EN:
		SET_BIT(RCC->APB1ENR, 4);
		break;
		
		case RCC_APB1_TIM7EN:
		SET_BIT(RCC->APB1ENR, 5);
		break;
		
		case RCC_APB1_WWDGEN:
		SET_BIT(RCC->APB1ENR, 11);
		break;
		
		case RCC_APB1_SPI2EN:
		SET_BIT(RCC->APB1ENR, 14);
		break;
		
		case RCC_APB1_SPI3EN:
		SET_BIT(RCC->APB1ENR, 15);
		break;
		
		case RCC_APB1_USART2EN:
		SET_BIT(RCC->APB1ENR, 17);
		break;
		
		case RCC_APB1_USART3EN:
		SET_BIT(RCC->APB1ENR, 18);
		break;
		
		case RCC_APB1_UART4EN:
		SET_BIT(RCC->APB1ENR, 19);
		break;
		
		case RCC_APB1_UART5EN:
		SET_BIT(RCC->APB1ENR, 20);
		break;
		
		case RCC_APB1_I2C1EN:
		SET_BIT(RCC->APB1ENR, 21);
		break;
		
		case RCC_APB1_I2C2EN:
		SET_BIT(RCC->APB1ENR, 22);
		break;
		
		case RCC_APB1_USBEN:
		SET_BIT(RCC->APB1ENR, 23);
		break;
		
		case RCC_APB1_CANEN:
		SET_BIT(RCC->APB1ENR, 25);
		break;
		
		case RCC_APB1_DAC2EN:
		SET_BIT(RCC->APB1ENR, 26);
		break;
		
		case RCC_APB1_PWREN:
		SET_BIT(RCC->APB1ENR, 28);
		break;
		
		case RCC_APB1_DAC1EN:
		SET_BIT(RCC->APB1ENR, 29);
		break;
		
		case RCC_APB1_I2C3EN:
		SET_BIT(RCC->APB1ENR, 30);
		break;
	}
}


void RCC_voidDisable_APB1_clock(RCC_APB1_peripherals_t copy_tPeripheral)
{
	switch(copy_tPeripheral)
	{
		case RCC_APB1_TIM2EN:
		CLR_BIT(RCC->APB1ENR, 0);
		break;
		
		case RCC_APB1_TIM3EN:
		CLR_BIT(RCC->APB1ENR, 1);
		break;
		
		case RCC_APB1_TIM4EN:
		CLR_BIT(RCC->APB1ENR, 2);
		break;
		
		case RCC_APB1_TIM6EN:
		CLR_BIT(RCC->APB1ENR, 4);
		break;
		
		case RCC_APB1_TIM7EN:
		CLR_BIT(RCC->APB1ENR, 5);
		break;
		
		case RCC_APB1_WWDGEN:
		CLR_BIT(RCC->APB1ENR, 11);
		break;
		
		case RCC_APB1_SPI2EN:
		CLR_BIT(RCC->APB1ENR, 14);
		break;
		
		case RCC_APB1_SPI3EN:
		CLR_BIT(RCC->APB1ENR, 15);
		break;
		
		case RCC_APB1_USART2EN:
		CLR_BIT(RCC->APB1ENR, 17);
		break;
		
		case RCC_APB1_USART3EN:
		CLR_BIT(RCC->APB1ENR, 18);
		break;
		
		case RCC_APB1_UART4EN:
		CLR_BIT(RCC->APB1ENR, 19);
		break;
		
		case RCC_APB1_UART5EN:
		CLR_BIT(RCC->APB1ENR, 20);
		break;
		
		case RCC_APB1_I2C1EN:
		CLR_BIT(RCC->APB1ENR, 21);
		break;
		
		case RCC_APB1_I2C2EN:
		CLR_BIT(RCC->APB1ENR, 22);
		break;
		
		case RCC_APB1_USBEN:
		CLR_BIT(RCC->APB1ENR, 23);
		break;
		
		case RCC_APB1_CANEN:
		CLR_BIT(RCC->APB1ENR, 25);
		break;
		
		case RCC_APB1_DAC2EN:
		CLR_BIT(RCC->APB1ENR, 26);
		break;
		
		case RCC_APB1_PWREN:
		CLR_BIT(RCC->APB1ENR, 28);
		break;
		
		case RCC_APB1_DAC1EN:
		CLR_BIT(RCC->APB1ENR, 29);
		break;
		
		case RCC_APB1_I2C3EN:
		CLR_BIT(RCC->APB1ENR, 30);
		break;
	}
}


void RCC_voidEnable_APB2_clock(RCC_APB2_peripherals_t copy_tPeripheral)
{
	switch(copy_tPeripheral)
	{
		case RCC_APB2_SYSCFGEN:
		SET_BIT(RCC->APB2ENR, 0);
		break;
		
		case RCC_APB2_TIM1EN:
		SET_BIT(RCC->APB2ENR, 11);
		break;
		
		case RCC_APB2_SPI1EN:
		SET_BIT(RCC->APB2ENR, 12);
		break;
		
		case RCC_APB2_TIM8EN:
		SET_BIT(RCC->APB2ENR, 13);
		break;
		
		case RCC_APB2_USART1EN:
		SET_BIT(RCC->APB2ENR, 14);
		break;
		
		case RCC_APB2_SPI4EN:
		SET_BIT(RCC->APB2ENR, 15);
		break;
		
		case RCC_APB2_TIM15EN:
		SET_BIT(RCC->APB2ENR, 16);
		break;
		
		case RCC_APB2_TIM16EN:
		SET_BIT(RCC->APB2ENR, 17);
		break;
		
		case RCC_APB2_TIM17EN:
		SET_BIT(RCC->APB2ENR, 18);
		break;
		
		case RCC_APB2_TIM20EN:
		SET_BIT(RCC->APB2ENR, 20);
		break;
	}
}


void RCC_voidDisable_APB2_clock(RCC_APB2_peripherals_t copy_tPeripheral)
{
	switch(copy_tPeripheral)
	{
		case RCC_APB2_SYSCFGEN:
		CLR_BIT(RCC->APB2ENR, 0);
		break;
		
		case RCC_APB2_TIM1EN:
		CLR_BIT(RCC->APB2ENR, 11);
		break;
		
		case RCC_APB2_SPI1EN:
		CLR_BIT(RCC->APB2ENR, 12);
		break;
		
		case RCC_APB2_TIM8EN:
		CLR_BIT(RCC->APB2ENR, 13);
		break;
		
		case RCC_APB2_USART1EN:
		CLR_BIT(RCC->APB2ENR, 14);
		break;
		
		case RCC_APB2_SPI4EN:
		CLR_BIT(RCC->APB2ENR, 15);
		break;
		
		case RCC_APB2_TIM15EN:
		CLR_BIT(RCC->APB2ENR, 16);
		break;
		
		case RCC_APB2_TIM16EN:
		CLR_BIT(RCC->APB2ENR, 17);
		break;
		
		case RCC_APB2_TIM17EN:
		CLR_BIT(RCC->APB2ENR, 18);
		break;
		
		case RCC_APB2_TIM20EN:
		CLR_BIT(RCC->APB2ENR, 20);
		break;
	}
}
