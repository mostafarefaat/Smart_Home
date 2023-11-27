/*
 * spi.h
 *
 * Created: 02-Nov-23 11:25:43 AM
 *  Author: mosta
 */ 

#include "../DIO Driver/dio.h"


#ifndef SPI_H_
#define SPI_H_

/*-----SPCR control register-----*/
#define SPR0 0
#define SPR1 1
#define CPHA 2
#define CPOL 3
#define MSTR 4
#define DORD 5
#define SPE 6
#define SPIE 7
/*-----SPSR status register-----*/
#define SPI2X 0
#define WCOL 6
#define SPIF 7
/*-----SPDR data register-----*/
#define LSB 0
#define MSB 7
/*-----SPI PINS-----*/
#define SS 4
#define MOSI 5
#define MISO 6
#define SCK 7

/*-----Orders-----*/
#define Open_Door 1
#define Close_Door 0
#define Turn_On 2
#define Turn_Off 3

/*-----Functions declaration-----*/
void Spi_Master_init(void);
void Spi_Master_send(uint8_t request);
void Spi_Master_receive(void);
void Spi_Slave_init(void);
uint8_t Spi_Slave_receive(void);



#endif /* SPI_H_ */