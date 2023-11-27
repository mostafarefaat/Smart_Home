/*
 * adc.c
 *
 * Created: 25-Oct-23 9:56:56 PM
 *  Author: mosta
 */ 
#include "adc.h"

void ADC_init(void)
{
	ADMUX |= (1<<REFS0);		// AVCC reference
	
	ADCSRA = 0x00 ;			//prescale  /2
	
	ADCSRA |= (1<<ADEN);	// Enable the ADC
}

uint16_t ADC_read(uint8_t channel)
{
	ADMUX |= (channel & 0x0F);	//Choose channel to be read
	
	ADCSRA |= (1<<ADSC);		//Start Conversion
	
	while( (ADCSRA & (1<<4)) == 0);	//Wait for conversion Complete flag

	return ADCL | (ADCH << 8);	//Return the digital value
	
}