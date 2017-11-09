/*
 * pwm.h
 *
 *  Created on: 04.12.2016
 *      Author: Spritkopf
 */

#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>


#define PWM_CH_R	1		/* tim3 ch 1 */
#define PWM_CH_G	2		/* tim3 ch 2 */
#define PWM_CH_B	3		/* tim3 ch 3 */


/* Init PWM (TIM3)
 * PWM Frequency: 1 kHz
 */


int8_t pwm_init(void);

/* set heater dutycyle ( 0.0 < duty < 1.0 ) */
void pwm_set_dutycyle(uint8_t channel, float duty);

int8_t pwm_start(void);
int8_t pwm_stop(void);


#endif /* PWM_H_ */
