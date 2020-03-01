
#include <atmega.h>
#include <i2c.h>
#include <debug.h>

#ifndef ATMEGA_I2C_ADDRESS
#define ATMEGA_I2C_ADDRESS 0x05
#endif

Atmega::Atmega() : i2c_(new I2c("Atmega::i2c", ATMEGA_I2C_ADDRESS))
{
  debug(ATMEGA, "Atmega::Atmega\n");
}

Atmega::~Atmega()
{
   delete i2c_;
}

int Atmega::writeI2c(uint8_t reg, const uint8_t* data, int length)
{
  pthread_mutex_lock(&communication_lock_);
  int ret = i2c_->write(reg, data, length);
  pthread_mutex_unlock(&communication_lock_);
  return ret;
}