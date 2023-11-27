/*
 * i2c.h
 *
 * Created: 09-Nov-23 2:17:23 PM
 *  Author: mosta
 */ 
#include "../DIO Driver/dio.h"
#include <math.h>

#ifndef I2C_H_
#define I2C_H_
/*--------------TWBR PINS--------------*/
#define TWBR0 0
#define TWBR1 1
#define TWBR2 2
#define TWBR3 3
#define TWBR4 4
#define TWBR5 5
#define TWBR6 6
#define TWBR7 7
/*--------------TWCR PINS--------------*/
#define TWIE 0
#define TWEN 2
#define TWWC 3
#define TWSTO 4
#define TWSTA 5
#define TWEA 6
#define TWINT 7
/*--------------TWSR PINS--------------*/
#define TWPS0 0
#define TWPS1 1
#define TWS3 3
#define TWS4 4
#define TWS5 5
#define TWS6 6
#define TWS7 7
/*--------------TWDR PINS--------------*/
#define TWD0 0
#define TWD1 1
#define TWD2 2
#define TWD3 3
#define TWD4 4
#define TWD5 5
#define TWD6 6
#define TWD7 7
/*--------------TWAR PINS--------------*/
#define TWGCE 0
#define TWA0 1
#define TWA1 2
#define TWA2 3
#define TWA3 4
#define TWA4 5
#define TWA5 6
#define TWA6 7

/*----------------------------*/

#define F_CPU 1000000U
#define SCL_CLK 400000U
#define BITRATE(TWSR) ((F_CPU/SCL_CLK)-16) / (2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))

#define WRITE 0
#define READ 1

#define ACK 0
#define NACK 1

/*--------------States--------------*/

#define START_STATE				0x08
#define REPEATED_START_STATE	0x10
#define SLA_W_ACK_STATE			0x18
#define SLA_W_NACK_STATE		0x20
#define SLA_R_ACK_STATE			0x40
#define SLA_R_NACK_STATE		0x48
#define DATA_WRITE_ACK_STATE	0x28
#define DATA_WRITE_NACK_STATE	0x30
#define DATA_READ_ACK_STATE		0x50
#define DATA_READ_NACK_STATE	0x58


/*--------------returns--------------*/
#define EVENT_OK					0
#define START_NOT_SENT				1
#define REPEATED_START_NOT_SENT		2
#define SLA_W_ACK_SENT				3
#define SLA_W_NACK_SENT				4
#define SLA_R_ACK_SENT				5
#define SLA_R_NACK_SENT				6
#define SLA_RW_FAILED				7
#define DATA_WRITE_ACK_SENT			8
#define DATA_WRITE_NACK_SENT		9
#define DATA_WRITE_FAILED			10
#define DATA_READ_ACK_SENT			11
#define DATA_READ_NACK_SENT			12
#define DATA_READ_FAILED			13
#define ENTER_READ_OR_WRITE			14


/*------------------------------------------*/

uint8_t data;

void I2C_Master_init(void);
void I2C_Master_send(void);
void I2C_Master_receive(void);
uint8_t I2C_start(void);
uint8_t REPEATED_I2C_start(void);
uint8_t I2C_address_select(uint8_t address, uint8_t rw);
uint8_t I2C_data_event(uint8_t *data, uint8_t rw, uint8_t ack);
void I2C_stop(void);








#endif /* I2C_H_ */