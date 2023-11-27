/*
 * eeprom.h
 *
 * Created: 16-Nov-23 7:34:43 PM
 *  Author: mosta
 */ 
#include "../../utilities/registers.h"

#ifndef EEPROM_H_
#define EEPROM_H_


void EEPROM_write(uint16_t uiAddress, uint8_t ucData);
uint8_t EEPROM_read(uint16_t uiAddress);


#endif /* EEPROM_H_ */