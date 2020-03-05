#ifndef CONTROL_HANDLER_H
#define CONTROL_HANDLER_H

class Atmega;
class GamePad;

class ControlHandler
{
  public:
    ControlHandler(GamePad* game_pad);
    ~ControlHandler();

    void gpioInit();
    void i2cInit();

    static void buttonCallback(); 

    static void* gpioFunction(void* arg);
    static void* i2cFunction(void* arg);

  private:
    ControlHandler();
    ControlHandler(const ControlHandler&);

    Atmega*  atmega_;
    GamePad* game_pad_;
};

#endif