/*
 * i2cSlave.c
 *
 * Created: 26.02.2020
 *  Author: Lukas
 *
 */

#include "config.h"
#include "I2cSlave.h"
#include <stdlib.h>
#include <util/twi.h>
#include <avr/interrupt.h>

//---------------------------------------------------------------------
static volatile uint8_t rxbuffer[256];
static volatile uint8_t txbuffer[256];
static volatile uint8_t buffer_address;
static volatile uint8_t start_buffer_address;
static void (*i2cSlaveRecv)(uint8_t*, uint8_t, uint8_t);
static void (*i2cSlaveReq)();

//---------------------------------------------------------------------
void i2cSlaveSetCallbacks(void (*recv)(uint8_t*, uint8_t, uint8_t), void (*req)())
{
  i2cSlaveRecv = recv;
  i2cSlaveReq  = req;
}

//---------------------------------------------------------------------
void i2cSlaveInit(uint8_t address)
{
  // load address into TWI address register
  TWAR = (address << 1);
  // set the TWCR to enable address matching and enable TWI, clear TWINT, enable TWI interrupt
  TWCR = (1<<TWIE) | (1<<TWEA) | (1<<TWINT) | (1<<TWEN);
}

//---------------------------------------------------------------------
ISR(TWI_vect)
{
  uint8_t data;
  uint8_t status = (TWSR & 0xf8);

  switch (status)
  {
    case TW_SR_SLA_ACK:
      buffer_address = 0xff;
      // clear TWI interrupt flag, prepare to receive next byte and acknowledge
      TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
      break;
    case TW_SR_DATA_ACK:
      data = TWDR;
      
      // check wether an address has already been transmitted or not
      if(buffer_address == 0xff)
      {
        buffer_address       = data; 
        start_buffer_address = data;
        
        // clear TWI interrupt flag, prepare to receive next byte and acknowledge
        TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
      }
      else if(buffer_address < 0xfe)
      {
        rxbuffer[buffer_address++] = data;
        // clear TWI interrupt flag, prepare to receive next byte and acknowledge
        TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
      }
      else
      {
        // Don't acknowledge
        TWCR &= ~(1<<TWEA); 
        // clear TWI interrupt flag, prepare to receive last byte.
        TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEN); 
      }
      break;
    /*
    case TW_ST_DATA_ACK:
      // device has been addressed to be a transmitter
      // copy data from TWDR to the temporary memory
      data = TWDR;
      
      // if no buffer read address has been sent yet
      if(buffer_address == 0xff)
      {
        buffer_address = data;
      }
      else if(buffer_address < 0xfe)
      {
        TWDR = txbuffer[buffer_address++];
        // clear TWI interrupt flag, prepare to send next byte and receive acknowledge
        TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEA) | (1<<TWEN); 
      }
      else
      {
        // Don't acknowledge
        TWCR &= ~(1<<TWEA); 
        // clear TWI interrupt flag, prepare to receive last byte.
        TWCR |= (1<<TWIE) | (1<<TWINT) | (1<<TWEN); 
      }
      break;
    */
    case 0xa0:
      // stop condition
      i2cSlaveRecv((uint8_t*)(rxbuffer + start_buffer_address), buffer_address - start_buffer_address, start_buffer_address);
      TWCR |= (1<<TWIE) | (1<<TWEA) | (1<<TWEN);
      break;
    default:
      // if none of the above apply prepare TWI to be addressed again
      TWCR |= (1<<TWIE) | (1<<TWEA) | (1<<TWEN);
      break;
  }
} 