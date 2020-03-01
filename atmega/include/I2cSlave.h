/*
 * i2cSlaveSlave.h
 *
 * Created: 26.02.2020
 *  Author: Lukas
 *
 */

#ifndef I2C_SLAVE_H
#define I2C_SLAVE_H

#include <avr/interrupt.h>

void i2cSlaveInit(uint8_t address);
void i2cSlaveStop(void);
void i2cSlaveSetCallbacks(void (*recv)(uint8_t*, uint8_t, uint8_t), void (*req)());

inline void __attribute__((always_inline)) i2cSlaveTransmitByte(uint8_t data)
{
  TWDR = data;
}

ISR(TWI_vect);

#endif