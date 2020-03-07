#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include <stdint.h>

class Gpio;

class Peripherial
{
  public:
    static Peripherial* instance();
    ~Peripherial();

    int initGpio();
    void initLed(uint8_t led_pin);
    void initButton(uint8_t button_pin, void (*f_ptr)());
    void heartBeat();

  private:
    Peripherial();

    static Peripherial* instance_;

    Gpio*  gpio_;
};

  
#endif