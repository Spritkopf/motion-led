/*
 * rgb_led.h
 *
 *  Created on: 23.11.2017
 *      Author: ricardo
 */

#ifndef INC_RGB_LED_H_
#define INC_RGB_LED_H_

#include <stdint.h>
/* type definition which describes the color in a HSV color wheel (saturation is always 1) */
typedef struct
{
	uint16_t angle;	/* angle of the color wheel (hue) */
	float brightness; /* relative brightness  (0.0 .. 1.0) */
}rgb_led_color_t;

extern rgb_led_color_t rgb_led_current_color;

void rgb_led_init(void);

/* sets pwm corresponding to the current values in rgb_led_current_color */
void rgb_led_update_color(void);



#endif /* INC_RGB_LED_H_ */
