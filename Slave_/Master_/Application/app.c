/*
 * app.c
 *
 * Created: 24-Nov-23 10:08:50 AM
 *  Author: mosta
 */ 
#include "app.h"

uint8_t data;
void app_init(void)
{
	
	DIO_init(PORT_D,PIN5,OUT); /*Makes PIN5 in PORT D output pin and initiate it by low*/
	DIO_init(PORT_D,PIN6,OUT); /*Makes PIN6 in PORT D output pin and initiate it by low*/
	DIO_init(PORT_D,PIN7,OUT); /*Makes PIN7 in PORT D output pin and initiate it by low*/
	
	DIO_write(PORT_D,PIN5,LOW);
	DIO_write(PORT_D,PIN6,LOW);
	DIO_write(PORT_D,PIN7,LOW);	

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

		


}