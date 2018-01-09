/*
 * adc.h
 *
 *  Created on: 01.12.2016
 *      Author: Spritkopf
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc_init(void);
void adc_deinit(void);
uint32_t adc_measure(void);


#endif /* ADC_H_ */
