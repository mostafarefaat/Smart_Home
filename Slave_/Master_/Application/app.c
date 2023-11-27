/*
 * app.c
 *
 * Created: 24-Nov-23 10:08:50 AM
 *  Author: mosta
 */ 
#include "app.h"


#define Vref 5
#define ADC_STEP Vref/1024.0
#define SENSOR_RESOLUTION (float)1 means -> 1 xVolt/x sensor reading

uint8_t data;

volatile uint16_t digital_value = 0;
void app_init(void)
{
	
	DIO_init(PORT_D,PIN5,OUT); /*Makes PIN5 in PORT D output pin and initiate it by low*/
	DIO_init(PORT_D,PIN6,OUT); /*Makes PIN6 in PORT D output pin and initiate it by low*/
	DIO_init(PORT_D,PIN7,OUT); /*Makes PIN7 in PORT D output pin and initiate it by low*/
		
	DIO_write(PORT_D,PIN5,LOW);
	DIO_write(PORT_D,PIN6,LOW);
	DIO_write(PORT_D,PIN7,LOW);	

	DDRC = 0xFF;	// Set PORTC to be output

	DDRD |= (1<<0) | (1<<1);	//Set PIN0 and PIN1 in PORTD to be outputs

	//ADC initializing
	DDRA &= ~(1<<0);	// Set ADC channel 0 to be input
	
	Spi_Slave_init();

}

void app_start(void)
{
	data = Spi_Slave_receive();
	PORTA = data;
	
	switch(data)
	{
		case Open_Door: servo_move_180_deg(); break;
		
		case Close_Door: servo_move_zero_deg(); break;
		
		case Turn_On: 
			DIO_write(PORT_D,PIN6,HIGH); 
			DIO_write(PORT_D,PIN7,HIGH);
			break; 
		case Turn_Off:
			DIO_write(PORT_D,PIN6,LOW);
			DIO_write(PORT_D,PIN7,LOW);
			break; 
	}
	ADC_init();	
	digital_value = ADC_read(ADC_CH_0);
	PORTC = (uint8_t)digital_value;

	PORTD = (uint8_t)(digital_value>>8);
}







/* temp_value = 0;
volatile float sensor_value = 0.0, analogue_value = 0.0;

// Read the value from ADC


// Write the value on the PINS


//Convert to Analog value
analogue_value = digital_value * ADC_STEP;

// Get the final to Analog value
sensor_value = analogue_value / SENSOR_RESOLUTION;*/