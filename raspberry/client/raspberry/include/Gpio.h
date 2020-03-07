#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <string>

class Gpio
{
  public:
    Gpio(std::string name);
    ~Gpio();

    void heartBeat();
    void initLed(uint8_t led_pin);
    void initButton(uint8_t button_pin, void (*f_ptr)());

  private:
    Gpio();

    std::string name_;

    uint8_t led_pin_;
    uint8_t button_pin_;
};

#endif