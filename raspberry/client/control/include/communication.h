
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>

class Communication
{
  public:
    enum Type
    {
      TYPE_I2C,
      TYPE_USART,
      TYPE_SPI
    };

    Communication(const char* name, enum Type com);
    ~Communication();

    virtual int write(uint8_t reg, const uint8_t* data, int length) = 0;
    virtual int read(uint8_t reg, uint8_t* data, int lenght) = 0;
    const char* getName();
    enum Type getType();
    
  private:
    Communication();
    const char* name_;
    enum Type   type_;
};

#endif
