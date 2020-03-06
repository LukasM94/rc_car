#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

class Gpio
{
  public:
    ~Gpio();
    static Gpio* instance();
    void heartBeat();
    void initLed();
    void initButton(void (*f_ptr)());

  private:
    Gpio();
    uint8_t led_pin_;
    uint8_t button_pin_;
    uint8_t i2c_sda_pin_;
    uint8_t i2c_clk_pin_;
    
    static Gpio* instance_;
};

#endif