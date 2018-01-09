/*
 * light_sensor.h
 *
 *  Created on: 29.11.2017
 *      Author: ricardo
 */

#ifndef INC_LIGHT_SENSOR_H_
#define INC_LIGHT_SENSOR_H_



#include <stdint.h>

void light_sensor_init(void);
void light_sensor_deinit(void);

/* perform a measurement and return result (0: it is dark, 1: it is light) */
uint8_t light_sensor_check_ambient_light(void);

#endif /* INC_LIGHT_SENSOR_H_ */
