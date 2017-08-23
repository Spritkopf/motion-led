/*
 * main.c
 *
 *  Created on: 23.08.2017
 *      Author: rbck
 */

#include "pwm.h"


int main(void)
{

	HAL_Init();

	PWM_Init();

	PWM_Start();



	while(1)
	{


	}

	return (0);
}


