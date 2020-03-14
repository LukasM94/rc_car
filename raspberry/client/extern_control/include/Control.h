#ifndef CONTROL_H
#define CONTROL_H

#include <atomic>

class UController;
class GamePad;

class Control
{
  public:
    static Control* instance();
    void setController(UController* u_controller);
    ~Control();

    void gpioInit();
    void gpioDeInit();
    void i2cInit();

    void resetUController();

    static void buttonCallback(); 

    static void* gpioFunction(void* arg);
    static void* i2cFunction(void* arg);

  private:
    Control();
    Control(const Control&);

    static void writeI2c(Control* ch, uint8_t reg, const uint8_t* data, int length);

    std::atomic_bool    i2c_running_;
    std::atomic_uint8_t i2c_error_;
    static const uint8_t I2C_ERROR_THRESHOLD = 5;

    static Control* instance_;

    UController* u_controller_;

    enum I2C_MODE { NORMAL, OFFSET };

    static const int8_t THRESHOLD_FOR_JOYSTICK = 50;
};

#endif