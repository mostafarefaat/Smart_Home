/*
 * i2c.c
 *
 * Created: 09-Nov-23 2:17:09 PM
 *  Author: mosta
 */ 
#include "i2c.h"

void I2C_Master_init(void)
{
	TWSR = 0x00; /*Choose prescaling*/
	TWBR = BITRATE(TWSR); /*set BitRate*/
}
void I2C_Master_send(void)
{
	if(I2C_start() == EVENT_OK)
	{
		if(I2C_address_select(0x10,WRITE) == SLA_W_ACK_SENT)
		{
			if(I2C_data_event(&data,WRITE,ACK) == DATA_WRITE_ACK_SENT)
			{
				I2C_stop();
			}
		}
	}	
	
}
void I2C_Master_receive(void)
{
	if(I2C_start() == EVENT_OK)
	{
		if(I2C_address_select(0x10,READ) == SLA_R_ACK_SENT)
		{
			if(I2C_data_event(&data,READ,NACK) == DATA_READ_NACK_SENT)
			{
				I2C_stop();
			}
		}
	}	
}

uint8_t I2C_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); /*clears TWINT flag to start new event, 
												enabling the I2C, sends start bit*/
	
	while(!(TWCR & (1<<TWINT))); /*waits until the start bit is sent 
									by waiting for the TWINT flag to be 1*/
	
	if((TWSR & 0xF8) != START_STATE )
	{
		return START_NOT_SENT;
	}
	else
	{
		return EVENT_OK;
	}
	
	
}

uint8_t REPEATED_I2C_start(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN); /*clears TWINT flag to start new event, 
												enabling the I2C, sends start bit*/
	
	while(!(TWCR & (1<<TWINT))); /*waits until the start bit is sent 
									by waiting for the TWINT flag to be 1*/
	
	if((TWSR & 0xF8) != REPEATED_START_STATE )
	{
		return REPEATED_START_NOT_SENT;
	}
	else
	{
		return EVENT_OK;
	}
}

uint8_t I2C_address_select(uint8_t address, uint8_t rw)
{	
	uint8_t status;
	if(rw == WRITE)
	{
		TWDR = address + 0; /*write SLA + W in I2C data register*/
	}
	else if(rw == READ)
	{
		TWDR = address + 1; /*write SLA + R in I2C data register*/
	}
	else
	{
		
	}
	
	TWCR = (1<<TWEN) | (1<<TWINT); /*enable the I2C & clear the TWINT flag
									to start new event */
	while(!(TWCR & (1<<TWINT))); /*wait until it finishes it current job 
										by waiting TWINT flag to be set*/
	status = TWSR & 0xF8;	/*Read I2C status register*/
	
	if(status == SLA_W_ACK_STATE) /*Check for SLA + W sent and ACK received*/
	{
		return SLA_W_ACK_SENT;
	}
	else if(status == SLA_W_NACK_STATE) /*Check for SLA + W sent and NACK received*/
	{
		return SLA_W_NACK_SENT;
	}
	if(status == SLA_R_ACK_STATE) /*Check for SLA + R sent and ACK received*/
	{		
		return SLA_R_ACK_SENT;
	}
	else if(status == SLA_R_NACK_STATE) /*Check for SLA + R sent and NACK received*/
	{
		return SLA_R_NACK_SENT;
	}
	else
	{
		return SLA_RW_FAILED;
	}	
}

uint8_t I2C_data_event(uint8_t *data, uint8_t rw, uint8_t ack)
{
	uint8_t status;
	
	if(rw == WRITE)
	{
		TWDR = *data;  /*Copy data in I2C data register*/
	
		TWCR = (1<<TWEN) | (1<<TWINT); /*enable the I2C & clear the TWINT flag
									to start new event */
		while(!(TWCR & (1<<TWINT))); /*wait until it finishes it current job 
										by waiting TWINT flag to be set*/
		status = TWSR & 0xF8;	/*Read I2C status register*/
	
		if(status == DATA_WRITE_ACK_STATE) /*Checks for data transmission and ACK received*/
		{
			return DATA_WRITE_ACK_SENT;
		}
		else if(status == DATA_WRITE_NACK_STATE) /*Checks for data transmission and NACK received*/
		{
			return DATA_WRITE_NACK_SENT;
		}
		else
		{
			return DATA_WRITE_FAILED; /*else returns transmission failed*/
		}	
	}
	else if(rw == READ)
	{
		if(ack == ACK)
		{
		TWCR = (1<<TWEN) | (1<<TWINT) | (1<<TWEA); /*enable the I2C & clear the TWINT flag
														to start new event & Generate ACK */
			
		}
		else if(ack == NACK)
		{
		TWCR = (1<<TWEN) | (1<<TWINT); /*enable the I2C & clear the TWINT flag
										to start new event & Don't Generate ACK */	
		}
		while(!(TWCR & (1<<TWINT))); /*wait until it finishes it current job 
										by waiting TWINT flag to be set*/
		*data = TWDR; /*Read Data*/
		
		status = TWSR & 0xF8;	/*Read I2C status register*/
		
		if(status == DATA_READ_ACK_STATE) /*Checks for data transmission and ACK received*/
		{
			return DATA_READ_ACK_SENT;
		}
		else if(status == DATA_READ_NACK_STATE ) /*Checks for data transmission and NACK received*/
		{
			return DATA_READ_NACK_SENT;
		}
		else
		{
			return DATA_READ_FAILED;  /*else returns transmission failed*/
		}
	
	}
	
	return ENTER_READ_OR_WRITE;
		
	
	
}

void I2C_stop(void)
{
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN); /*clears TWINT flag to start new event,
													 enabling the I2C, sends STOP bit*/
	
	while((TWCR & (1<<TWSTO))); /*WAIT UNTIL STOP CONDITION EXECUTION*/
}