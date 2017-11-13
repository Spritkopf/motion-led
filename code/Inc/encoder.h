/*
 * encoder.h
 *
 *  Created on: 13.03.2016
 *      Author: Spritkopf
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#define ENCODER_BTN_PIN	 GPIO_PIN_2

void encoder_init(void);

void encoder_start(void);
void encoder_stop(void);


void encoder_set_rotation_callback(void (*user_callback)(uint8_t direction));
void encoder_set_button_callback(void (*user_callback)(void));

void encoder_button_interrupt_handler(void);
#endif /* ENCODER_H_ */
