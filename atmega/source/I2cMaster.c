/*
 * i2c.c
 *
 * Created: 25.02.2020
 *  Author: Lukas 
 *
 */

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

//---------------------------------------------------------------------
#include <avr/io.h>
#include <util/twi.h>
#include <assert.h>

#include "I2cMaster.h"

#define TIMEOUT 0xffff

//---------------------------------------------------------------------
void i2cInit(void)
{
	TWBR = (uint8_t)TWBR_val;
}

//---------------------------------------------------------------------
uint8_t i2cStart(uint8_t address)
{
	int32_t timeout = TIMEOUT;
	// reset TWI control register
	TWCR = 0;
	// transmit START condition 
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	// wait for end of transmission
	while(!(TWCR & (1<<TWINT)) && timeout--);
	
	// check if the start condition was successfully transmitted
	if((TWSR & 0xF8) != TW_START)
	{ 
		return -1; 
	}
	
	// load slave address into data register
	TWDR = address;
	// start transmission of address
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while(!(TWCR & (1<<TWINT)) && timeout--);
	
	// check if the device has acknowledged the READ / WRITE mode
	uint8_t twst = TW_STATUS & 0xF8;
	if ((twst != TW_MT_SLA_ACK) && (twst != TW_MR_SLA_ACK)) 
	{
		return -2;
	}
	
	if (timeout == 0)
	{
		return -3;
	}
	return 0;
}

//---------------------------------------------------------------------
uint8_t i2cWrite(uint8_t data)
{
	int32_t timeout = TIMEOUT;
	// load data into data register
	TWDR = data;
	// start transmission of data
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while(!(TWCR & (1<<TWINT)) && timeout--);
	
	if((TWSR & 0xF8) != TW_MT_DATA_ACK)
	{ 
		return -4; 
	}
	
	if (timeout == 0)
	{
		return -5;
	}
	return 0;
}

//---------------------------------------------------------------------
uint8_t i2cReadAck(void)
{
	int32_t timeout = TIMEOUT;
	// start TWI module and acknowledge data after reception
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA); 
	// wait for end of transmission
	while(!(TWCR & (1<<TWINT)) && timeout--);
	// return received data from TWDR
	return TWDR;
}

//---------------------------------------------------------------------
uint8_t i2cReadNack(void)
{
	int32_t timeout = TIMEOUT;
	// start receiving without acknowledging reception
	TWCR = (1<<TWINT) | (1<<TWEN);
	// wait for end of transmission
	while(!(TWCR & (1<<TWINT)) && timeout--);
	// return received data from TWDR
	return TWDR;
}

//---------------------------------------------------------------------
uint8_t i2cTransmit(uint8_t address, uint8_t* data, uint16_t length)
{
	uint8_t ret;
	if ((ret = i2cStart(address | I2C_WRITE)) != 0) 
	{
		return ret;
	}
	
	for (uint16_t i = 0; i < length; i++)
	{
		uint8_t ret;
		if ((ret = i2cWrite(data[i])) != 0) 
		{
			return ret;
		}
	}
	
	i2cStop();
	
	return 0;
}

//---------------------------------------------------------------------
uint8_t i2cReceive(uint8_t address, uint8_t* data, uint16_t length)
{
	uint8_t ret;
	if ((ret = i2cStart(address | I2C_READ)) != 0) 
	{
		return ret;
	}
	
	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = i2cReadAck();
	}
	data[(length-1)] = i2cReadNack();
	
	i2cStop();
	
	return 0;
}

//---------------------------------------------------------------------
uint8_t i2cWriteReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{
	uint8_t ret;
	if ((ret = i2cStart(devaddr | I2C_WRITE)) != 0) 
	{
		return ret;
	}

	i2cWrite(regaddr);

	for (uint16_t i = 0; i < length; i++)
	{
		if ((ret = i2cWrite(data[i])) != 0) 
		{
			return ret;
		}
	}

	i2cStop();

	return 0;
}

//---------------------------------------------------------------------
uint8_t i2cReadReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length)
{
	uint8_t ret;
	if ((ret = i2cStart(devaddr)) != 0) 
	{
		return ret;
	}

	i2cWrite(regaddr);

	if ((ret = i2cStart(devaddr | 0x01)) != 0)
	{
		return ret;
	} 

	for (uint16_t i = 0; i < (length-1); i++)
	{
		data[i] = i2cReadAck();
	}
	data[(length-1)] = i2cReadNack();

	i2cStop();

	return 0;
}

//---------------------------------------------------------------------
void i2cStop(void)
{
	// transmit STOP condition
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
}