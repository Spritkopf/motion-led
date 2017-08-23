/*
 * colorwheel.h
 *
 *  Created on: 18.02.2016
 *      Author: Spritkopf
 */

#ifndef COLORWHEEL_H_
#define COLORWHEEL_H_

#include <stdint.h>

void Colorwheel_SetBrightness(uint8_t brightness, uint8_t *buf_r, uint8_t *buf_g, uint8_t *buf_b);
uint8_t Colorwheel_GetRGB(uint16_t angle, uint8_t *buf_r, uint8_t *buf_g, uint8_t *buf_b);

#endif /* COLORWHEEL_H_ */
