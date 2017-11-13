/*
 * colorwheel.h
 *
 *  Created on: 18.02.2016
 *      Author: Spritkopf
 */

#ifndef COLORWHEEL_H_
#define COLORWHEEL_H_

#include <stdint.h>

uint8_t colorwheel_get_rgb(uint16_t angle, uint8_t *buf_r, uint8_t *buf_g, uint8_t *buf_b);
void colorwheel_set_brightness(uint8_t brightness, uint8_t* buf_r, uint8_t* buf_g, uint8_t* buf_b);

#endif /* COLORWHEEL_H_ */
