/*
 * pwm.c
 *
 *  Created on: 04.12.2016
 *      Author: Spritkopf
 */

#include "stm32l1xx_hal.h"

#include "pwm.h"

#define PWM_PIN_CH1 		GPIO_PIN_4
#define PWM_PIN_CH2 		GPIO_PIN_5
#define PWM_PIN_CH3 		GPIO_PIN_0
#define PWM_GPIO_Port 		GPIOB

#define  PERIOD_VALUE       (uint32_t)(30000-1)  /* Period Value (1us * 30000 = 30ms)  */

/* Timer handler declaration */
TIM_HandleTypeDef htim;


int8_t pwm_init(void)
{
	GPIO_InitTypeDef   GPIO_InitStruct;
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_OC_InitTypeDef sConfigOC;
	uint32_t clock_freq;
	uint32_t uhPrescalerValue;

	clock_freq = HAL_RCC_GetPCLK1Freq();
	uhPrescalerValue = clock_freq/10000000;	/* 1 tick = 10us */

	__HAL_RCC_TIM3_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin = PWM_PIN_CH1 | PWM_PIN_CH2 | PWM_PIN_CH3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM3;
	HAL_GPIO_Init(PWM_GPIO_Port, &GPIO_InitStruct);


	htim.Instance = TIM3;
	htim.Init.Prescaler = uhPrescalerValue;
	htim.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim.Init.Period = PERIOD_VALUE;
	htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	if (HAL_TIM_Base_Init(&htim) != HAL_OK)
	{
		return (-1);
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim, &sClockSourceConfig) != HAL_OK)
	{
		return (-1);
	}

	if (HAL_TIM_PWM_Init(&htim) != HAL_OK)
	{
		return (-1);
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM2;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	if ((HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) ||
			(HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) ||
			(HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_3) != HAL_OK))
	{
		return (-1);
	}
	return (0);

}

int8_t pwm_start(void)
{
	if( (HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1) != HAL_OK) ||
		(HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_2) != HAL_OK) ||
		(HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_3) != HAL_OK))
	{
		return (-1);
	}
	return (0);
}

int8_t pwm_stop(void)
{
	if( (HAL_TIM_PWM_Stop(&htim, TIM_CHANNEL_1) != HAL_OK) ||
		(HAL_TIM_PWM_Stop(&htim, TIM_CHANNEL_2) != HAL_OK) ||
		(HAL_TIM_PWM_Stop(&htim, TIM_CHANNEL_3) != HAL_OK))
	{
		return (-1);
	}

	return (0);
}

void pwm_set_dutycyle(uint8_t channel, float duty)
{
	if(duty > 1) { duty = 1; }
	if(duty < 0) { duty = 0; }

	switch (channel)
	{
	case 1:
		TIM3->CCR1 = (uint16_t)(PERIOD_VALUE * duty);
		break;
	case 2:
		TIM3->CCR2 = (uint16_t)(PERIOD_VALUE * duty);
		break;
	case 3:
		TIM3->CCR3 = (uint16_t)(PERIOD_VALUE * duty);
		break;
	default:
		break;
	}

}
