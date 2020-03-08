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
    inline void toggleGreenLed()
    {
      toggleLed(led_green_pin_);
    }
    inline void toggleRedLed()
    {
      toggleLed(led_red_pin_);
    }
    inline void onGreenLed()
    {
      onLed(led_green_pin_);
    }
    inline void onRedLed()
    {
      onLed(led_red_pin_);
    }
    inline void offGreenLed()
    {
      offLed(led_green_pin_);
    }
    inline void offRedLed()
    {
      offLed(led_red_pin_);
    }

  private:
    Gpio();

    int initLed(uint8_t led_pin);
    void toggleLed(uint8_t led_pin);
    void onLed(uint8_t led_pin);
    void offLed(uint8_t led_pin);

    std::string name_;

    uint8_t led_green_pin_;
    uint8_t led_red_pin_;
    uint8_t button_pin_;
};

#endif