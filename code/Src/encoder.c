/*
 * encoder.c
 *
 *  Created on: 13.03.2016
 *      Author: Spritkopf
 */

#include "stm32l1xx_hal.h"
#include "encoder.h"

#define CH_A_HIGH	HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11)==GPIO_PIN_SET
#define CH_A_LOW	HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_11)==GPIO_PIN_RESET
#define CH_B_HIGH	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==GPIO_PIN_SET
#define CH_B_LOW	HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8)==GPIO_PIN_RESET
#define THRESHOLD	300

#define ENCODER_PIN_A	GPIO_PIN_6
#define ENCODER_PIN_B	GPIO_PIN_7
#define ENCODER_PORT	GPIOB


/* Timer handler declaration */
TIM_HandleTypeDef    encoder_handle;


static uint32_t encoder_get_direction();

/* function pointer for callback functions */
void (*encoder_rotation_callback)(uint8_t direction);
void (*encoder_button_callback)(void);

void TIM4_IRQHandler(void)
{
	uint8_t temp_direction;

	HAL_TIM_IRQHandler(&encoder_handle);

	temp_direction = encoder_get_direction();
	encoder_rotation_callback(temp_direction);

	/* Wait a short delay before clearing Interrupt flags to avoid
	 * immediately following interrupts due to bouncing issues
	 *  todo: remove this, we have hardware debouncing */
	//delay = 0xfff0;
	//while(delay--);


}


void encoder_init()
{
	GPIO_InitTypeDef   gpio;
	TIM_Encoder_InitTypeDef encoder_config;

	/* Encoder Pins
	 *
	 * A: PA8
	 * B: PE11
	 * Button: PA6
	 */


	/* Enable GPIO Channels Clock */
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();
	__HAL_RCC_TIM4_CLK_ENABLE();

	HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);


	/*##-2- Configure I/Os #####################################################*/
	/* Common configuration for all channels */
	gpio.Pin = ENCODER_PIN_A | ENCODER_PIN_B;
	gpio.Mode = GPIO_MODE_AF_PP;
	gpio.Pull = GPIO_NOPULL;
	gpio.Speed = GPIO_SPEED_HIGH;
	gpio.Alternate = GPIO_AF2_TIM4;

	/* Channel 2 configuration */
	HAL_GPIO_Init(ENCODER_PORT, &gpio);
#if 0
	/* Push Button Initialization */
	GPIO_InitStruct.Pin = GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
	HAL_GPIO_Init(ENCODER_PORT, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 2);
	HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);
#endif

	encoder_handle.Instance = TIM4;
	encoder_handle.Init.Period = 0xFFFF;
	encoder_handle.Init.Prescaler = 0;
	encoder_handle.Init.ClockDivision = 0;
	encoder_handle.Init.CounterMode = TIM_COUNTERMODE_UP;

	encoder_config.EncoderMode = TIM_ENCODERMODE_TI2;
	encoder_config.IC1Polarity = TIM_ICPOLARITY_FALLING;
	encoder_config.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	encoder_config.IC1Prescaler = TIM_ICPSC_DIV1;
	encoder_config.IC1Filter = 0x0F;

	encoder_config.IC2Polarity = TIM_ICPOLARITY_BOTHEDGE;
	encoder_config.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	encoder_config.IC2Prescaler = TIM_ICPSC_DIV1;
	encoder_config.IC2Filter = 0x0F;

	HAL_TIM_Encoder_Init(&encoder_handle, &encoder_config);




}

void encoder_start(void)
{
	/* Start the encoder interface */
	HAL_TIM_Encoder_Start_IT(&encoder_handle, TIM_CHANNEL_1);
}

void encoder_stop(void)
{
	HAL_TIM_Encoder_Stop_IT(&encoder_handle, TIM_CHANNEL_1);
}

uint32_t encoder_get_direction(void)
{
	return (__HAL_TIM_IS_TIM_COUNTING_DOWN(&encoder_handle));
}

void encoder_set_rotation_callback(void (*user_callback)(uint8_t direction))
{
	encoder_rotation_callback = user_callback;
}

void encoder_set_button_callback(void (*user_callback)(void))
{
	encoder_button_callback = user_callback;

}

