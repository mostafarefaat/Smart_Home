/*
 * adc.h
 *
 * Created: 25-Oct-23 9:57:18 PM
 *  Author: mosta
 */ 
#include "../../utilities/bit_manipulation.h"
#include "../../utilities/registers.h"


#ifndef ADC_H_
#define ADC_H_

/*ADMUX PINS*/
#define MUX0 0
#define MUX1 1
#define MUX2 2
#define MUX3 3
#define MUX4 4
#define ADLAR 5
#define REFS0 6
#define REFS1 7

/*ADCSRA PINS*/
#define ADPS0 0
#define ADPS1 1
#define ADPS2 2
#define ADIE 3
#define ADIF 4
#define ADATE 5
#define ADSC 6
#define ADEN 7

/*ADC Channels*/
#define ADC_CH_0 0
#define ADC_CH_1 1
#define ADC_CH_2 2
#define ADC_CH_3 3
#define ADC_CH_4 4
#define ADC_CH_5 5
#define ADC_CH_6 6
#define ADC_CH_7 7

/*Functions Prototype*/

void ADC_init(void);
uint16_t ADC_read(uint8_t channel);



#endif /* ADC_H_ */