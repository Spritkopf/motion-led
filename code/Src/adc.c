/*
 * adc.c
 *
 *  Created on: 01.12.2016
 *      Author: Spritkopf
 */

#include "stm32l1xx_hal.h"
#include "adc.h"

#define ADC_INSTANCE			ADC1
#define ADC_CLK_ENABLE 			__HAL_RCC_ADC1_CLK_ENABLE
#define PHOTO_R_Pin 			GPIO_PIN_0
#define PHOTO_R_GPIO_Port 		GPIOA
#define PHOTO_R_GPIO_CLK_ENABLE	__HAL_RCC_GPIOA_CLK_ENABLE


ADC_HandleTypeDef hadc;

void adc_init(void)
{
	/* PC1   Channel 11 Adc 1-3 */
	GPIO_InitTypeDef gpio;
	ADC_ChannelConfTypeDef channel_config;

	PHOTO_R_GPIO_CLK_ENABLE();
	ADC_CLK_ENABLE();

	gpio.Pin = PHOTO_R_Pin;
    gpio.Mode = GPIO_MODE_ANALOG;
    gpio.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(PHOTO_R_GPIO_Port, &gpio);

	hadc.Instance = ADC_INSTANCE;
	hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
	hadc.Init.Resolution = ADC_RESOLUTION_12B;
	hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
	hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
	hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
	hadc.Init.LowPowerAutoWait = ADC_AUTOWAIT_DISABLE;
	hadc.Init.LowPowerAutoPowerOff = ADC_AUTOPOWEROFF_DISABLE;
	hadc.Init.ChannelsBank = ADC_CHANNELS_BANK_A;
	hadc.Init.ContinuousConvMode = ENABLE;
	hadc.Init.NbrOfConversion = 1;
	hadc.Init.DiscontinuousConvMode = DISABLE;
	hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
	hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
	hadc.Init.DMAContinuousRequests = DISABLE;
	if (HAL_ADC_Init(&hadc) != HAL_OK)
	{
	}

	channel_config.Channel = ADC_CHANNEL_0;
	channel_config.Rank = 1;
	channel_config.SamplingTime = ADC_SAMPLETIME_384CYCLES;

	if (HAL_ADC_ConfigChannel(&hadc, &channel_config) != HAL_OK)
	{

	}
	HAL_Delay(50);  /* Wait for ADC to settle */

	HAL_ADC_Start(&hadc);
}


uint32_t adc_measure(void)
{
	if (HAL_ADC_PollForConversion(&hadc, 1000) == HAL_OK)
	{
		return (HAL_ADC_GetValue(&hadc));
	}
	return (0);
}
