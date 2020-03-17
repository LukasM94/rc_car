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
    int initLedGreen(uint8_t led_pin);
    int initLedRed(uint8_t led_pin);
    int initResetButton(uint8_t reset_pin);
    int initButton(uint8_t button_pin, void (*f_ptr)());
    void resetUcontroller();
    void resetResetPin();
    void setResetPin();
    void heartBeat();
    void turnGreenLedOff();
    void turnRedLedOn();
    void turnRedLedOff();
    void toggleRedLed();

  private:
    Peripherial();

    static Peripherial* instance_;

    Gpio*  gpio_;
};

  
#endif