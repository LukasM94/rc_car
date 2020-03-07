
#ifndef ATMEGA_H
#define ATMEGA_H

#include <UController.h>

class Atmega : public UController
{
  public:
    Atmega();
    ~Atmega();

    virtual int writeI2c(uint8_t reg, const uint8_t* data, int length);
    virtual int writeUsart(uint8_t reg, const uint8_t* data, int length);
    virtual int writeSpi(uint8_t reg, const uint8_t* data, int length);
};

#endif