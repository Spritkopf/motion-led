/*
 * light_sensor.c
 *
 *  Created on: 29.11.2017
 *      Author: ricardo
 */
#include "light_sensor.h"
#include "adc.h"

#define LIGHT_SENSOR_THRESHOLD		1000  /* this is the ADC value above it is assumed it is bright outside adjust for your specific sensor (trial-and-error)*/

void light_sensor_init(void)
{
	adc_init();
}

/* perform a measurement and return result (0: it is dark, 1: it is light) */
uint8_t light_sensor_check_ambient_light(void)
{

	if(adc_measure() > LIGHT_SENSOR_THRESHOLD)
	{
		return (1);
	}
	else
	{
		return (0);
	}
}
