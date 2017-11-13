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
#define EEPROM_IDENT	1

config_bank_t config_bank;
#if 0
void SETTINGS_test2(void){
	uint16_t i;
	uint8_t test[12] = {4,2,3,4,2,6,7,8,1,10,11,12};
	uint8_t test2[12];
	T_RGB_PRESET preset;

	preset.r=128;
	preset.g=5;
	preset.b=6;
	strncpy(preset.name, "aaaaaaaa", sizeof(preset.name));
	SETTINGS_SavePreset2(1, &preset);
	SETTINGS_SavePreset2(3, &preset);
	SETTINGS_SavePreset2(5, &preset);

	/*
	 *
	for(i = 0; i < 3; i++)
	{
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,(uint32_t)(0x08080500+i*4), (uint32_t)*(((uint32_t*)&confbank)+i));
	}

	HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,EEPROM_ADDR+0x500,test[0]);
	HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,EEPROM_ADDR+0x501,test[1]);
	HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,EEPROM_ADDR+0x502,test[2]);
	HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,EEPROM_ADDR+0x503,test[3]);
	*/
}
void SETTINGS_test(void)
{
	typedef struct
	{
		uint16_t eeprom_ident;
		T_RGB_PRESET presets[3];
		T_SETTINGS settings;
	} T_CONFBANK_TEMP;
	uint8_t i;
	uint32_t* mem_temp = NULL;

	T_CONFBANK_TEMP confbank_temp1;
	uint32_t* confbank_temp_memory1 = &confbank_temp1;

	T_RGB_PRESET preset2;
	uint32_t index_presets;

	confbank_temp1.eeprom_ident = 5;
	confbank_temp1.settings.fade_speed = 3;
	strncpy(confbank_temp1.presets[0].name, "hallo_1", sizeof(confbank_temp1.presets[0].name));
	confbank_temp1.presets[0].r = 255;
	confbank_temp1.presets[0].g = 128;
	confbank_temp1.presets[0].b = 64;
	strncpy(confbank_temp1.presets[1].name, "bla", sizeof(confbank_temp1.presets[1].name));
	confbank_temp1.presets[1].r = 1;
	confbank_temp1.presets[1].g = 2;
	confbank_temp1.presets[1].b = 3;
	strncpy(confbank_temp1.presets[2].name, "foobar", sizeof(confbank_temp1.presets[2].name));
	confbank_temp1.presets[2].r = 0xA;
	confbank_temp1.presets[2].g = 0xB;
	confbank_temp1.presets[2].b = 0xC;

	index_presets = offsetof(T_CONFBANK_TEMP, presets)+1*sizeof(T_RGB_PRESET);
	HAL_FLASHEx_DATAEEPROM_Unlock();
	for(i = 0; i < (sizeof(confbank_temp1)/sizeof(uint32_t))+1; i++)
	{
		HAL_FLASHEx_DATAEEPROM_Erase(FLASH_TYPEERASEDATA_WORD,EEPROM_ADDR+0x400+(i*sizeof(uint32_t)));
	}
	for(i = 0; i < (sizeof(confbank_temp1)/sizeof(uint32_t))+1; i++)
	{
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,EEPROM_ADDR+0x400+(i*sizeof(uint32_t)),*(confbank_temp_memory1+i));
	}
	HAL_FLASHEx_DATAEEPROM_Lock();


	HAL_FLASHEx_DATAEEPROM_Unlock();
	memcpy(&preset2, (uint32_t*)(EEPROM_ADDR+0x0400+index_presets), sizeof(preset2));
	preset2.r = 5;
	preset2.g = 6;
	preset2.b = 7;
	mem_temp = calloc(1, sizeof(preset2)+2*(sizeof(uint32_t)));
	memcpy(mem_temp, (uint32_t*)(EEPROM_ADDR+0x0400+index_presets), sizeof(preset2)+2*(sizeof(uint32_t)));
	memcpy(mem_temp, &preset2, sizeof(preset2));
	for(i = 0; i < ((sizeof(preset2)/sizeof(uint32_t))+1); i++)
	{
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,EEPROM_ADDR+0x0400+index_presets+(i*sizeof(uint32_t)),*(mem_temp+i));
	}
	HAL_FLASHEx_DATAEEPROM_Lock();
}


bool SETTINGS_Init(void)
{
	uint16_t confbank_size =  sizeof(confbank);
	uint16_t i;
	uint16_t ident;
	uint8_t index;
	uint32_t* confbank_temp_memory = (uint32_t*)&confbank;

	if(confbank_size >= EEPROM_MAX_SIZE)
	{
		return (false);
	}
	memset(&confbank, 0, sizeof(confbank));

	/* check EEPROM_IDENT */
	index = offsetof(T_CONFBANK, eeprom_ident)/4;
	ident = (uint16_t)((*(uint32_t*)(EEPROM_ADDR+0x500+index))&0x0000FFFF);
	/* check if confbank structure has changed */
	if(ident != EEPROM_IDENT)
	{
		/* structure has changed, erase confbank and reprogram */
		HAL_FLASHEx_DATAEEPROM_Unlock();

		for(i = 0; i < (sizeof(confbank)/sizeof(uint32_t))+1; i++)
		{
			HAL_FLASHEx_DATAEEPROM_Erase(FLASH_TYPEERASEDATA_WORD,EEPROM_ADDR+0x500+(i*sizeof(uint32_t)));
		}

		confbank.eeprom_ident = EEPROM_IDENT;
		confbank.settings.fade_speed = 3;

		for(i = 0; i < (sizeof(confbank)/sizeof(uint32_t))+1; i++)
		{
			HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_WORD,EEPROM_ADDR+0x500+(i*sizeof(uint32_t)), *(confbank_temp_memory+(i)));
		}
		HAL_FLASHEx_DATAEEPROM_Lock();


	}

	memcpy(&confbank, (uint32_t*)(EEPROM_ADDR+0x500), sizeof(confbank));

	return (true);
}


bool SETTINGS_SavePreset(uint8_t preset_num, T_RGB_PRESET* preset)
{
	uint8_t* pnt_preset;
	uint32_t index_preset;
	uint32_t i;

	if(preset_num >= NUM_RGB_PRESETS)
	{
		return (false);
	}
	/* get pointer to preset */
	pnt_preset = (uint8_t*)(&(confbank.presets[preset_num]));

	/* update preset in confbank */
	memcpy(pnt_preset, preset, sizeof(T_RGB_PRESET));

	index_preset = offsetof(T_CONFBANK, presets)+preset_num*sizeof(T_RGB_PRESET);

	HAL_FLASHEx_DATAEEPROM_Unlock();

	for(i = 0; i < sizeof(T_RGB_PRESET); i++)
	{
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,EEPROM_ADDR+index_preset+(i),*pnt_preset);
		pnt_preset++;
	}
	HAL_FLASHEx_DATAEEPROM_Lock();

	return (true);
}


bool SETTINGS_SavePreset2(uint8_t preset_num, T_RGB_PRESET* preset)
{
	uint32_t index_preset;
	uint32_t i;

	if(preset_num >= NUM_RGB_PRESETS)
	{
		return (false);
	}

	/* update preset in confbank */
	memcpy((uint8_t*)(&(confbank.presets[preset_num])), preset, sizeof(T_RGB_PRESET));

	/* replace NULL with whitespaces (workaround for FLASH-write-bug */
	for(i=0; i<sizeof(confbank.presets[preset_num]); i++)
	{
		if(confbank.presets[preset_num].name[i]==0){
			confbank.presets[preset_num].name[i] = 32;
		}
	}


	index_preset = offsetof(T_CONFBANK, presets[preset_num]);

	HAL_FLASHEx_DATAEEPROM_Unlock();
	for(i = 0; i < sizeof(T_RGB_PRESET); i++)
	{
		HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,EEPROM_ADDR+0x500+index_preset+(i),(uint32_t)*(((uint8_t*)&confbank)+index_preset+(i)));
		HAL_Delay(1);
	}
	HAL_FLASHEx_DATAEEPROM_Lock();

	return (true);
}

bool SETTINGS_SaveSettings(uint8_t fadespeed)
{
	uint32_t index_preset;


	/* update settings in confbank */
	confbank.settings.fade_speed = fadespeed;

	index_preset = offsetof(T_CONFBANK, settings);

	HAL_FLASHEx_DATAEEPROM_Unlock();
	HAL_FLASHEx_DATAEEPROM_Program(FLASH_TYPEPROGRAMDATA_BYTE,EEPROM_ADDR+0x500+index_preset,(uint32_t)confbank.settings.fade_speed);
	HAL_FLASHEx_DATAEEPROM_Lock();

	return (true);
}


bool SETTINGS_LoadPreset(uint8_t preset_num, T_RGB_PRESET* preset)
{
	//uint32_t index_preset;
	if(preset_num >= NUM_RGB_PRESETS)
	{
		return (false);
	}
	/* index_preset = offsetof(T_CONFBANK, presets)+preset_num*sizeof(T_RGB_PRESET); */

	/*memcpy(preset, (uint32_t*)(EEPROM_ADDR+index_preset), sizeof(T_RGB_PRESET)); */
	memcpy(preset, &confbank.presets[preset_num], sizeof(T_RGB_PRESET));

	return (true);
}
#endif
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
