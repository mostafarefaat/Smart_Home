/*
 * spi.c
 *
 * Created: 02-Nov-23 11:25:36 AM
 *  Author: mosta
 */ 
#include "spi.h"

uint8_t flush_buffer = 0;

void Spi_Master_init(void)
{
	DDRA = 0xFF;
	//initialize the IN and OUT PINS
	DIO_init(PORT_B,SS,OUT);
	DIO_init(PORT_B,SCK,OUT);
	DIO_init(PORT_B,MOSI,OUT);
	DIO_init(PORT_B,MISO,IN);
	
	//initialize Slave select pin to be high
	DIO_write(PORT_B,SS,HIGH);
	
	//Select Master mode, prescale of /16, enable the SPI
	SPCR |= (1<<SPE) | (1<<MSTR) | (1<<SPR1); 
	//disable the double SPI speed bit
	SPSR &= ~ (1<<SPI2X);
	
}
void Spi_Master_send(void)
{
	
	DIO_write(PORT_B,SS,LOW);
	
	SPDR = 'B';
	
	while(READ_BIT(SPSR,SPIF) == 0);
	
	flush_buffer = SPDR;
	
	DIO_write(PORT_B,SS,HIGH);
	
}
void Spi_Master_receive(void)
{
	SPDR = 0xFF;
	
	while(READ_BIT(SPSR,SPIF) == 0);
	
	flush_buffer = SPDR;
	
	PORTA = flush_buffer;	

}

void Spi_Slave_init(void)
{
	DDRA = 0xFF;
	//initialize the IN and OUT PINS
	DIO_init(PORT_B,SS,IN);
	DIO_init(PORT_B,SCK,IN);
	DIO_init(PORT_B,MOSI,IN);
	DIO_init(PORT_B,MISO,OUT);
	//Select Master mode, prescale of /16, enable the SPI
	SPCR |= (1<<SPE) | (1<<SPR1);
	//disable the double SPI speed bit
	SPSR &= ~ (1<<SPI2X);	
}
uint8_t Spi_Slave_receive(void)
{
	SPDR = 0xFF;
	
	while(READ_BIT(SPSR,SPIF) == 0);
	
	return SPDR;	
}