/*
 *
 * @file GPIO_interface.h
 * @author Kareem Hussein
 * @brief header file that contain GPIO public functions prototyoes, macros and declarations
 * @date 18/08/2024      
 * @version 1.0
 *
 */
 
#ifndef RCC_INTERFACE_H_
#define RCC_INTERFACE_H_


typedef enum
{
	RCC_CLK_HSI,
	RCC_CLK_HSE,
	RCC_CLK_PLL,
}RCC_clkType_t;

typedef enum
{
	RCC_CLK_OFF,
	RCC_CLK_ON,
}RCC_clkStatus_t;

typedef enum
{
	RCC_HSE_BY1,
	RCC_HSE_BY2,
}RCC_HSE_prescaler_t;

typedef enum
{
	RCC_PLL_MUL_2 = 0,
	RCC_PLL_MUL_3,
	RCC_PLL_MUL_4,
	RCC_PLL_MUL_5,
	RCC_PLL_MUL_6,
	RCC_PLL_MUL_7,
	RCC_PLL_MUL_8,
	RCC_PLL_MUL_9,
	RCC_PLL_MUL_10,
	RCC_PLL_MUL_11,
	RCC_PLL_MUL_12,
	RCC_PLL_MUL_13,
	RCC_PLL_MUL_14,
	RCC_PLL_MUL_15,
	RCC_PLL_MUL_16,
}RCC_PLL_mulFactor_t;

typedef enum
{
	RCC_PLL_SOURCE_HSI = 0,
	RCC_PLL_SOURCE_HSE,
}RCC_PLL_source_t;

typedef enum
{
	RCC_APB2_HCLK_BY1 = 0,
	RCC_APB2_HCLK_BY2,
	RCC_APB2_HCLK_BY4,
	RCC_APB2_HCLK_BY8,
	RCC_APB2_HCLK_BY16,
}RCC_APB2_prescaler_t;

typedef enum
{
	RCC_APB1_HCLK_BY1 = 0,
	RCC_APB1_HCLK_BY2,
	RCC_APB1_HCLK_BY4,
	RCC_APB1_HCLK_BY8,
	RCC_APB1_HCLK_BY16,
}RCC_APB1_prescaler_t;

typedef enum
{
	RCC_AHB_SYSCLK_BY1 = 0,
	RCC_AHB_SYSCLK_BY2,
	RCC_AHB_SYSCLK_BY4,
	RCC_AHB_SYSCLK_BY8,
	RCC_AHB_SYSCLK_BY16,
	RCC_AHB_SYSCLK_BY64,
	RCC_AHB_SYSCLK_BY128,
	RCC_AHB_SYSCLK_BY256,
	RCC_AHB_SYSCLK_BY512,
}RCC_AHB_prescaler_t;

typedef enum
{
	RCC_AHB_DMA1EN = 0,
	RCC_AHB_DMA2EN,
	RCC_AHB_SRAMEN,
	RCC_AHB_FLITFEN,
	RCC_AHB_FMCEN,
	RCC_AHB_CRCEN,
	RCC_AHB_IOPHEN,
	RCC_AHB_IOPAEN,
	RCC_AHB_IOPBEN,
	RCC_AHB_IOPCEN,
	RCC_AHB_IOPDEN,
	RCC_AHB_IOPEEN,
	RCC_AHB_IOPFEN,
	RCC_AHB_IOPGEN,
	RCC_AHB_TSCEN,
	RCC_AHB_ADC12EN,
	RCC_AHB_ADC34EN,
}RCC_AHB_peripherals_t;

typedef enum
{
	RCC_APB1_TIM2EN = 0,
	RCC_APB1_TIM3EN,
	RCC_APB1_TIM4EN,
	RCC_APB1_TIM6EN,
	RCC_APB1_TIM7EN,
	RCC_APB1_WWDGEN,
	RCC_APB1_SPI2EN,
	RCC_APB1_SPI3EN,
	RCC_APB1_USART2EN,
	RCC_APB1_USART3EN,
	RCC_APB1_UART4EN,
	RCC_APB1_UART5EN,
	RCC_APB1_I2C1EN,
	RCC_APB1_I2C2EN,
	RCC_APB1_USBEN,
	RCC_APB1_CANEN,
	RCC_APB1_DAC2EN,
	RCC_APB1_PWREN,
	RCC_APB1_DAC1EN,
	RCC_APB1_I2C3EN,
}RCC_APB1_peripherals_t;

typedef enum
{
	RCC_APB2_SYSCFGEN,
	RCC_APB2_TIM1EN,
	RCC_APB2_SPI1EN,
	RCC_APB2_TIM8EN,
	RCC_APB2_USART1EN,
	RCC_APB2_SPI4EN,
	RCC_APB2_TIM15EN,
	RCC_APB2_TIM16EN,
	RCC_APB2_TIM17EN,
	RCC_APB2_TIM20EN,
}RCC_APB2_peripherals_t;


void RCC_voidSetClockStatus(RCC_clkType_t copy_tClockType, RCC_clkStatus_t copy_tClockStatus);
void RCC_voidSetSystemClock(RCC_clkType_t copy_tClockType);
void RCC_voidSet_HSE_configurations(RCC_HSE_prescaler_t copy_tPrescaler);
void RCC_voidSet_PLL_configurations(RCC_PLL_source_t copy_tSource, RCC_PLL_mulFactor_t copy_tMultiplicationFactor);
void RCC_voidSet_APB2_clockPrescaler(RCC_APB2_prescaler_t copy_tPrescaler);
void RCC_voidSet_APB1_clockPrescaler(RCC_APB1_prescaler_t copy_tPrescaler);
void RCC_voidSet_AHB_clockPrescaler(RCC_AHB_prescaler_t copy_tPrescaler);
void RCC_voidEnable_AHB_clock(RCC_AHB_peripherals_t copy_tPeripheral);
void RCC_voidDisable_AHB_clock(RCC_AHB_peripherals_t copy_tPeripheral);
void RCC_voidEnable_APB1_clock(RCC_APB1_peripherals_t copy_tPeripheral);
void RCC_voidDisable_APB1_clock(RCC_APB1_peripherals_t copy_tPeripheral);
void RCC_voidEnable_APB2_clock(RCC_APB2_peripherals_t copy_tPeripheral);
void RCC_voidDisable_APB2_clock(RCC_APB2_peripherals_t copy_tPeripheral);


#endif
