/*
 * app.c
 *
 * Created: 24-Nov-23 10:08:50 AM
 *  Author: mosta
 */ 
#include "app.h"


#define Vref 5.0
#define ADC_STEP Vref/1024.0
#define SENSOR_RESOLUTION (float)10 /*means -> 1 xVolt/x sensor reading*/

uint8_t data;

uint8_t welcome_string[] = "Welcome";
uint8_t done_string[] = "Temp in C = ";

uint8_t value[4];

uint8_t Sensor_value, Sensor_value_copy;

volatile uint16_t digital_value = 0;
volatile uint16_t decimal = 0,weight = 1;
volatile uint8_t rem = 0;

void app_init(void)
{
	/*DIO PINS Config*/
	DIO_init(PORT_D,PIN5,OUT); DIO_write(PORT_D,PIN5,LOW); /*Makes PIN5 in PORT D output pin and initiate it by low*/
	DIO_init(PORT_D,PIN6,OUT); DIO_write(PORT_D,PIN6,LOW); /*Makes PIN6 in PORT D output pin and initiate it by low*/
	DIO_init(PORT_D,PIN7,OUT); DIO_write(PORT_D,PIN7,LOW); /*Makes PIN7 in PORT D output pin and initiate it by low*/
	DIO_init(PORT_B,PIN3,OUT); DIO_write(PORT_B,PIN3,LOW); /*Makes PIN3 in PORT B output pin and initiate it by low*/
	
	/*SPI and LCD initialize*/
	Spi_Slave_init();
	LCD_4_bit_init();
	
	//ADC initializing
	DIO_init(PORT_A,PIN0,IN);
	ADC_init();

}

void app_start(void)
{
	data = Spi_Slave_receive();
	PORTA = data;
	
	switch(data)
	{
		case Open_Door: servo_move_90_deg(); break;
		
		case Close_Door: servo_move_negative_90_deg(); break;
		
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
		case Get_Temp:
			 Temp_sensor_read();
		default: break;
	}

	if(Sensor_value_copy >= 25)
	{
		TCCR0 = 0x61;
		OCR0 = 100;
	}
	else
	{
		TCCR0 = 0x00;
	}
	
}
void clear_temp_string(uint8_t *str)
{
		uint8_t i;
		for(i=0; *(str + i) != 0; i++)	//send each character until str is null
		{
			*(str + i) = 0x20; // reset them to white spaces
		}
}
void display_Temp_on_LCD(void)
{
	LCD_4_bit_sendChar(value[1]);
	LCD_4_bit_sendChar(value[0]);	
}
void Temp_sensor_read(void)
{
	LCD_4_bit_sendCommand(0x01); //clears the LCD
	
	digital_value = ADC_read(ADC_CH_0); // Read the value from ADC
	
	Sensor_value = (digital_value * (ADC_STEP)) * 10;
	
	Sensor_value_copy = Sensor_value;
	
	LCD_4_bit_sendString(done_string); // indicates the conversion finished
	
	decimal = 0; weight = 1; rem = 0;
	uint8_t index = 0;
	/*Extracts the each number and put it in the value string for display*/
	while(Sensor_value != 0)
	{
		value[index] = (Sensor_value % 10) + (0x30);
		Sensor_value = Sensor_value/10;
		index++;
	}
	display_Temp_on_LCD();
	clear_temp_string(value); // resets the value strings	
	

}













