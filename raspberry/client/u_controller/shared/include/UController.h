
#ifndef U_CONTROLLER_H
#define U_CONTROLLER_H

#include <stdint.h>
#include <pthread.h>

class I2c;
class Usart;
class Spi;

class UController
{
  public:
    UController();
    ~UController();

    int initI2c();
    int initUsart();
    int initSpi();

    virtual int writeI2c(uint8_t reg, const uint8_t* data, int length) = 0;
    virtual int writeUsart(uint8_t reg, const uint8_t* data, int length) = 0;
    virtual int writeSpi(uint8_t reg, const uint8_t* data, int length) = 0;

  protected:
    I2c*   i2c_;
    Usart* usart_;
    Spi*   spi_;

    pthread_mutex_t communication_lock_;
};

#endif