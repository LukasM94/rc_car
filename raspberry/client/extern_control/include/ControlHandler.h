#ifndef CONTROL_HANDLER_H
#define CONTROL_HANDLER_H

class UController;
class GamePad;

class ControlHandler
{
  public:
    ControlHandler(UController* u_controller);
    ~ControlHandler();

    void gpioInit();
    void i2cInit();

    static void buttonCallback(); 

    static void* gpioFunction(void* arg);
    static void* i2cFunction(void* arg);

  private:
    ControlHandler();
    ControlHandler(const ControlHandler&);

    UController* u_controller_;

    enum I2C_MODE { NORMAL, OFFSET };

    static const int8_t THRESHOLD_FOR_JOYSTICK = 50;
};

#endif