/*
 * settings.c
 *
 *  Created on: 02.07.2016
 *      Author: Spritkopf
 */

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "settings.h"
#include "stm32l1xx_hal.h"

#define EEPROM_ADDR		FLASH_EEPROM_BASE
#define EEPROM_MAX_SIZE 0x0800
#define EEPROM_IDENT	2

config_bank_t config_bank;

int8_t settings_init(void)
{
	uint16_t confbank_size =  sizeof(config_bank);
	uint16_t i;
	uint16_t ident;
	uint8_t index;
	uint32_t* confbank_temp_memory = (uint32_t*)&config_bank;

	if(confbank_size >= EEPROM_MAX_SIZE)
	{
		return (-1);
	}
	memset(&config_bank, 0, confbank_size);

	/* check EEPROM_IDENT */
	index = offsetof(config_bank_t, eeprom_ident)/4;
	ident = (uint16_t)((*(uint32_t*)(EEPROM_ADDR+0x500+index))&0x0000FFFF);

	/* check if confbank structure has changed */
	if(ident != EEPROM_IDENT)
	{
		/* structure has changed, erase confbank and reprogram */
		HAL_FLASHEx_DATAEEPROM_Unlock();

		for(i = 0; i < (confbank_size/sizeof(uint32_t))+1; i++)
		{
			HAL_FLASHEx_DATAEEPROM_Erase(FLASH_TYPEERASEDATA_WORD,EEPROM_ADDR+0x500+(i*sizeof(uint32_t)));
		}

		config_bank.eeprom_ident = EEPROM_IDENT;

		for(i = 0; i < (confbank_size/sizeof(uint32_t))+1; i++)
		{
			HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,EEPROM_ADDR+0x500+(i*sizeof(uint32_t)), *(confbank_temp_memory+(i)));
		}
		HAL_FLASHEx_DATAEEPROM_Lock();


	}

	memcpy(&config_bank, (uint32_t*)(EEPROM_ADDR+0x500), confbank_size);

	return (0);
}

int8_t settings_save(void)
{
	uint32_t i;
	uint8_t* confbank = (uint8_t*)&config_bank;
	/* update settings in confbank */


	HAL_FLASHEx_DATAEEPROM_Unlock();
	for(i=0; i<sizeof(config_bank_t); i++)
	{
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,EEPROM_ADDR+0x500+i,(uint32_t)*confbank);
		confbank++;
	}
	HAL_FLASHEx_DATAEEPROM_Lock();

	return (0);
}
int8_t settings_load(void)
{
	return (0);
}
