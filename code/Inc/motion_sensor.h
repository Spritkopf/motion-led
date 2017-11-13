/*
 * motion_sensor.h
 *
 *  Created on: 31.08.2017
 *      Author: ricardo
 */

#ifndef INC_MOTION_SENSOR_H_
#define INC_MOTION_SENSOR_H_

#define MOTION_SENSOR_GPIO_PIN			GPIO_PIN_1

void motion_sensor_init(void(*cb)(void));

void motion_sensor_interrupt_handler();

#endif /* INC_MOTION_SENSOR_H_ */
