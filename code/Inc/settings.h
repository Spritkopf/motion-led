/*
 * settings.h
 *
 *  Created on: 02.07.2016
 *      Author: Spritkopf
 *
 *      Save and restore settings in internal EEPROM memory
 *      - 10 RGB user presets, the first will be loaded on-startup
 *      - Configuration bank for device settings ... tbd
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

typedef struct
{
	uint16_t eeprom_ident;
	uint8_t r;			/* R value */
	uint8_t g;			/* G value */
	uint8_t b;			/* B value */
	uint8_t brightness; /* brightness value */
} config_bank_t;

config_bank_t config_bank;

int8_t settings_init(void);

int8_t settings_save(void);
int8_t settings_load(void);

#endif /* SETTINGS_H_ */
