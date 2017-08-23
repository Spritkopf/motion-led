/*
 * pwm.h
 *
 *  Created on: 04.12.2016
 *      Author: Spritkopf
 */

#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>


#define PWM_CH_R	1		/* tim ch 1 */
#define PWM_CH_G	2		/* tim ch 2 */
#define PWM_CH_B	3		/* tim ch 3 */


/* Init PWM (TIM10)
 * PWM Frequency: 1 kHz
 */


void PWM_Init(void);

/* set heater dutycyle ( 0.0 < duty < 1.0 ) */
void PWM_SetDutyCyle(uint8_t channel, float duty);

void PWM_Start(void);
void PWM_Stop(void);


#endif /* PWM_H_ */
