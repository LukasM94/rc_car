
#ifndef SPI_H
#define SPI_H

#include <communication.h>

class Spi: public Communication
{
  public:
    Spi(const char* name);
    ~Spi();
    virtual int write(uint8_t reg, const uint8_t* data, int length);
    virtual int read(uint8_t reg, uint8_t* data, int lenght);

  private:
    Spi();
};

#endif