
#ifndef U_CONTROLLER_H
#define U_CONTROLLER_H

#include <stdint.h>
#include <pthread.h>
#include <string>

class I2c;
class Usart;
class Spi;
class Gpio;

class UController
{
  public:
    UController(const char* name);
    ~UController();

    int initI2c();
    int initUsart();
    int initSpi();
    int initGpio();
    void initLed(uint8_t led_pin);
    void initButton(uint8_t button_pin, void (*f_ptr)());
    void heartBeat();

    virtual int writeI2c(uint8_t reg, const uint8_t* data, int length) = 0;
    virtual int writeUsart(uint8_t reg, const uint8_t* data, int length) = 0;
    virtual int writeSpi(uint8_t reg, const uint8_t* data, int length) = 0;

  protected:
    UController();

    I2c*   i2c_;
    Usart* usart_;
    Spi*   spi_;
    Gpio*  gpio_;

    std::string name_;

    pthread_mutex_t communication_lock_;
};

#endif