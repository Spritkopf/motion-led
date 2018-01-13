/*
 * light_sensor.h
 *
 *  Created on: 29.11.2017
 *      Author: ricardo
 */

#ifndef INC_LIGHT_SENSOR_H_
#define INC_LIGHT_SENSOR_H_


#include <stdint.h>

#define LIGHT_SENSOR_THRESHOLD		1000  /* this is the ADC value above it is assumed it is bright outside adjust for your specific sensor (trial-and-error)*/



void light_sensor_init(void);
void light_sensor_deinit(void);
uint32_t light_sensor_get_value(void);

#endif /* INC_LIGHT_SENSOR_H_ */
