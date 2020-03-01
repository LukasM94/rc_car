
#ifndef I2C_H
#define I2C_H

#include <communication.h>

class I2c: public Communication
{
  public:
    I2c(const char* name, int dev_addrss);
    ~I2c();
    virtual int write(uint8_t reg, const uint8_t* data, int length);
    virtual int read(uint8_t reg, uint8_t* data, int lenght);

  private:
    int fd_;

    I2c();
    int writeByte(uint8_t reg, uint8_t data);
    int writeWord(uint8_t reg, const uint8_t* data);
    int writeBlock(uint8_t reg, const uint8_t* data, int length);
    void dataToHexArray(char* string, uint8_t* data, int length);
};

#endif