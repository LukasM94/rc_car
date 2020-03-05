
#ifndef USART_H
#define USART_H

#include <Communication.h>

class Usart: public Communication
{
  public:
    Usart(const char* name);
    ~Usart();
    virtual int write(uint8_t reg, const uint8_t* data, int length);
    virtual int read(uint8_t reg, uint8_t* data, int lenght);

  private:
    Usart();
};

#endif