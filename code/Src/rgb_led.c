/*
 * rgb_led.c
 *
 *  Created on: 24.11.2017
 *      Author: ricardo
 */

#include "rgb_led.h"
#include "pwm.h"
#include "colorwheel.h"

rgb_led_color_t rgb_led_current_color;

void rgb_led_init(void)
{
	/* initilaize pwm for controlling the LED strip */
	pwm_init();
	pwm_start();
}

/* sets pwm corresponding to the current values in rgb_led_current_color */
void rgb_led_update_color(void)
{
	uint8_t color_r = 0;
	uint8_t color_g = 0;
	uint8_t color_b = 0;

	colorwheel_get_rgb(rgb_led_current_color.angle, &color_r, &color_g, &color_b);
	pwm_set_dutycyle(PWM_CH_R, ((float)color_r * rgb_led_current_color.brightness)/255.0f);
	pwm_set_dutycyle(PWM_CH_G, ((float)color_g * rgb_led_current_color.brightness)/255.0f);
	pwm_set_dutycyle(PWM_CH_B, ((float)color_b * rgb_led_current_color.brightness)/255.0f);
}


