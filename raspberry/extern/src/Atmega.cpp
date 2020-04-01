
#include <Atmega.h>
#include <I2c.h>
#include <debug.h>

#ifndef ATMEGA_I2C_ADDRESS
#define ATMEGA_I2C_ADDRESS 0x05
#endif

Atmega::Atmega() : UController("Atmega")
{
  debug(ATMEGA, "ctor\n");
}

Atmega::~Atmega()
{
  debug(ATMEGA, "dtor\n");
}

int Atmega::writeI2c(uint8_t reg, const uint8_t* data, int length)
{
  communication_lock_.lock();
  int ret = i2c_->write(reg, data, length);
  communication_lock_.unlock();
  return ret;
}

int Atmega::writeUsart(uint8_t reg, const uint8_t* data, int length)
{
  return -1;
}

int Atmega::writeSpi(uint8_t reg, const uint8_t* data, int length)
{
  return -1;
}
