/*
 * motion_sensor.c
 *
 *  Created on: 31.08.2017
 *      Author: ricardo
 */

#include "stm32l1xx_hal.h"
#include "motion_sensor.h"

#define MOTION_SENSOR_GPIO_CLK_ENABLE	__HAL_RCC_GPIOA_CLK_ENABLE
#define MOTION_SENSOR_GPIO_PORT			GPIOA
#define MOTION_SENSOR_GPIO_PIN			GPIO_PIN_1
#define MOTION_SENSOR_IRQN				EXTI1_IRQn

void (*motion_callback)(void);

void motion_sensor_init(void(*cb)(void))
{
	GPIO_InitTypeDef gpio;

	MOTION_SENSOR_GPIO_CLK_ENABLE();

	gpio.Pin = MOTION_SENSOR_GPIO_PIN;
	gpio.Mode = GPIO_MODE_IT_RISING;
	gpio.Speed = GPIO_SPEED_LOW;
	gpio.Pull = GPIO_PULLDOWN;

	HAL_GPIO_Init(MOTION_SENSOR_GPIO_PORT, &gpio);

	HAL_NVIC_SetPriority(MOTION_SENSOR_IRQN, 15, 4);
	HAL_NVIC_EnableIRQ(MOTION_SENSOR_IRQN);

	/* register callback */
	motion_callback = cb;

}

void motion_sensor_interrupt_handler()
{
	if(motion_callback != NULL)
	{
		motion_callback();
	}
}
