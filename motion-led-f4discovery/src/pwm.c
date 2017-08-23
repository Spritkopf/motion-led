/*
 * pwm.c
 *
 *  Created on: 04.12.2016
 *      Author: Spritkopf
 */

#include "stm32f4xx_hal.h"

#include "pwm.h"

#define PWM_PIN_CH1 		GPIO_PIN_6
#define PWM_PIN_CH2 		GPIO_PIN_7
#define PWM_PIN_CH3 		GPIO_PIN_8
#define PWM_GPIO_Port 		GPIOC

#define  PERIOD_VALUE       (uint32_t)(30000-1)  /* Period Value (1us * 30000 = 30ms)  */

/* Timer handler declaration */
TIM_HandleTypeDef htim8;

float current_heater_pwm = 0;

void PWM_Error_Handler(void);

void PWM_Init(void)
{
	/* TIM8 Channel1  */
	GPIO_InitTypeDef   GPIO_InitStruct;
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_OC_InitTypeDef sConfigOC;
	uint32_t clock_freq;
	uint32_t uhPrescalerValue;

	clock_freq = HAL_RCC_GetPCLK1Freq();
	uhPrescalerValue = clock_freq/10000000;	/* 1 tick = 10us */

	__HAL_RCC_TIM8_CLK_ENABLE();
	__HAL_RCC_GPIOC_CLK_ENABLE();

	GPIO_InitStruct.Pin = PWM_PIN_CH1 | PWM_PIN_CH2 | PWM_PIN_CH3;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	GPIO_InitStruct.Alternate = GPIO_AF3_TIM8;
	HAL_GPIO_Init(PWM_GPIO_Port, &GPIO_InitStruct);

	clock_freq = HAL_RCC_GetPCLK1Freq();

	htim8.Instance = TIM8;
	htim8.Init.Prescaler = uhPrescalerValue;
	htim8.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim8.Init.Period = PERIOD_VALUE;
	htim8.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	if (HAL_TIM_Base_Init(&htim8) != HAL_OK)
	{
		PWM_Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim8, &sClockSourceConfig) != HAL_OK)
	{
		PWM_Error_Handler();
	}

	if (HAL_TIM_PWM_Init(&htim8) != HAL_OK)
	{
		PWM_Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM2;
	sConfigOC.Pulse = 0;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_LOW;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	if ((HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK) ||
			(HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK) ||
			(HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK))
	{
		PWM_Error_Handler();
	}

}

void PWM_Start(void)
{
	if( (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1) != HAL_OK) ||
		(HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2) != HAL_OK) ||
		(HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3) != HAL_OK))
	{
		PWM_Error_Handler();
	}
}

void PWM_Stop(void)
{
	if( (HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1) != HAL_OK) ||
		(HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_2) != HAL_OK) ||
		(HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_3) != HAL_OK))
	{
		PWM_Error_Handler();
	}
}

void PWM_SetDutyCyle(uint8_t channel, float duty)
{
	if(duty > 1) { duty = 1; }
	if(duty < 0) { duty = 0; }

	switch (channel)
	{
	case 1:
		TIM8->CCR1 = (uint16_t)(PERIOD_VALUE * duty);
		break;
	case 2:
		TIM8->CCR2 = (uint16_t)(PERIOD_VALUE * duty);
		break;
	case 3:
		TIM8->CCR3 = (uint16_t)(PERIOD_VALUE * duty);
		break;
	default:
		break;
	}

}

void PWM_Error_Handler(void)
{
	while(1)
	{
		/* PWM ERROR */
	}
}
