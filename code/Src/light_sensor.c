/*
 * light_sensor.c
 *
 *  Created on: 29.11.2017
 *      Author: ricardo
 */
#include "light_sensor.h"
#include "adc.h"



void light_sensor_init(void)
{
	adc_init();
}


void light_sensor_deinit(void)
{
	adc_deinit();
}

/* perform a measurement and return the adc value */
uint32_t light_sensor_get_value(void)
{

	return (adc_measure());

}
