
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <string>

class Communication
{
  public:
    enum Type
    {
      TYPE_I2C,
      TYPE_USART,
      TYPE_SPI
    };

    Communication(std::string name, enum Type com);
    ~Communication();

    virtual int write(uint8_t reg, const uint8_t* data, int length) = 0;
    virtual int read(uint8_t reg, uint8_t* data, int lenght) = 0;
    std::string& getName();
    enum Type getType();
    
  private:
    Communication();
    std::string name_;
    enum Type   type_;
};

#endif
