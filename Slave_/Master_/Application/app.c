/*
 * app.c
 *
 * Created: 24-Nov-23 10:08:50 AM
 *  Author: mosta
 */ 
#include "app.h"


#define Vref 5.0
#define ADC_STEP Vref/1024.0
#define SENSOR_RESOLUTION (float)1 /*means -> 1 xVolt/x sensor reading*/

uint8_t data;

uint8_t welcome_string[] = "Welcome";
uint8_t done_string[] = "ADC value is:";

volatile uint16_t digital_value = 0;
volatile uint16_t decimal = 0,weight = 1;
volatile uint8_t rem = 0 ;
volatile uint8_t x1=0;

void app_init(void)
{
	
	DIO_init(PORT_D,PIN5,OUT); /*Makes PIN5 in PORT D output pin and initiate it by low*/
	DIO_init(PORT_D,PIN6,OUT); /*Makes PIN6 in PORT D output pin and initiate it by low*/
	DIO_init(PORT_D,PIN7,OUT); /*Makes PIN7 in PORT D output pin and initiate it by low*/
		
	DIO_write(PORT_D,PIN5,LOW);
	DIO_write(PORT_D,PIN6,LOW);
	DIO_write(PORT_D,PIN7,LOW);	
	
	Spi_Slave_init();
	LCD_4_bit_init();
	ADC_init();	

	//ADC initializing
	DDRA &= ~(1<<0);
}

void app_start(void)
{
	data = Spi_Slave_receive();
	PORTA = data;
	
	switch(data)
	{
		case Open_Door: servo_move_180_deg(); break;
		
		case Close_Door: servo_move_zero_deg(); break;
		
		case Open_Temp_LCD:
		LCD_4_bit_sendString(welcome_string);
		TIMER0_delay(3000,no_prescale);
		LCD_4_bit_sendCommand(0x01);
		break;
		
		case Turn_On: 
			DIO_write(PORT_D,PIN6,HIGH); 
			DIO_write(PORT_D,PIN7,HIGH);
			break; 
		case Turn_Off:
			DIO_write(PORT_D,PIN6,LOW);
			DIO_write(PORT_D,PIN7,LOW);
			break; 
	}
	
	// Read the value from ADC
	digital_value = ADC_read(ADC_CH_0);
	decimal = 0; weight = 1; rem = 0;
	LCD_4_bit_sendCommand(0x01);
	LCD_4_bit_sendString(done_string);
	TIMER0_delay(3000,no_prescale);
	LCD_4_bit_sendCommand(0x01);
	
	while(digital_value != 0)
	{
	LCD_4_bit_sendChar((digital_value % 10) + (0x30));
	digital_value = digital_value/10;		
	}
	
}
















