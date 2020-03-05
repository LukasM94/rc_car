
#ifndef ATMEGA_H
#define ATMEGA_H

#include <stdint.h>
#include <pthread.h>

class I2c;

class Atmega
{
  public:
    Atmega();
    ~Atmega();

    int writeI2c(uint8_t reg, const uint8_t* data, int length);

  private:
    I2c*       i2c_;
    pthread_mutex_t communication_lock_;
};

#endif