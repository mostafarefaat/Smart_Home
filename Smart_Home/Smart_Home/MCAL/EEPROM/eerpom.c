/*
 * eerpom.c
 *
 * Created: 16-Nov-23 7:34:32 PM
 *  Author: mosta
 */ 
#include "eeprom.h"

void EEPROM_write(uint16_t uiAddress, uint8_t ucData)
{
	while(EECR & (1<<EEWE));
	
	EEARL = uiAddress;
	EEDR = ucData;
	
	EECR |= (1<<EEMWE);
	
	EECR |= (1<<EEWE);
}
uint8_t EEPROM_read(uint16_t uiAddress)
{
	while(EECR & (1<<EEWE));
	
	EEARL = uiAddress;
	
	EECR |= (1<<EERE);
	
	return EEDR;
	
	
}