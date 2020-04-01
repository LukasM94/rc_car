#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>
#include <string>

class Gpio
{
  public:
    Gpio(std::string name);
    ~Gpio();

    int initLedGreen(uint8_t led_pin);
    int initLedRed(uint8_t led_pin);
    int initButton(uint8_t button_pin, void (*f_ptr)());
    int initReset(uint8_t reset_pin);
    inline int toggleGreenLed()
    {
      return togglePin(led_green_pin_);
    }
    inline int toggleRedLed()
    {
      return togglePin(led_red_pin_);
    }
    inline int onGreenLed()
    {
      return setPin(led_green_pin_);
    }
    inline int onRedLed()
    {
      return setPin(led_red_pin_);
    }
    inline int offGreenLed()
    {
      return resetPin(led_green_pin_);
    }
    inline int offRedLed()
    {
      return resetPin(led_red_pin_);
    }
    inline int resetResetPin()
    {
      return resetPin(reset_pin_);
    }
    inline int setResetPin()
    {
      return setPin(reset_pin_);
    }

  private:
    Gpio();

    int initLed(uint8_t led_pin);
    int togglePin(uint8_t pin);
    int setPin(uint8_t pin);
    int resetPin(uint8_t pin);

    std::string name_;

    uint8_t led_green_pin_;
    uint8_t led_red_pin_;
    uint8_t button_pin_;
    uint8_t reset_pin_;
};

#endif