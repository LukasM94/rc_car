/*
 * i2c.h
 *
 * Created: 30.04.2017
 *  Author: Lukas   (copied from the web)
 *
 */


#ifndef I2C_MASTER_H
#define I2C_MASTER_H

#ifndef  F_CPU
#define F_CPU 16000000UL
#endif

#define I2C_READ 0x01
#define I2C_WRITE 0x00

#define F_SCL 400000UL // SCL frequency
#define Prescaler 1
#define TWBR_val ((((F_CPU / F_SCL) / Prescaler) - 16 ) / 2)

void i2cInit(void);
uint8_t i2cStart(uint8_t address);
uint8_t i2cWrite(uint8_t data);
uint8_t i2cReadAck(void);
uint8_t i2cReadNack(void);
uint8_t i2cTransmit(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2cReceive(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2cWriteReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t i2cReadReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
void i2cStop(void);

#endif // I2C_MASTER_H