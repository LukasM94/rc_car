#ifndef CONTROL_HANDLER_H
#define CONTROL_HANDLER_H

#include <map>
#include <Lock.h>
#include <WorkingThread.h>

class I2cHandler;
class GpioHandler;
class UController;

class ControlHandler : public WorkingThread
{
  public:
    ControlHandler(UController* u_controller);
    ~ControlHandler();

    virtual void run();

  private:
    friend GpioHandler;
    friend I2cHandler;
    
    ControlHandler();
    ControlHandler(const ControlHandler&);

    I2cHandler*  i2c_handler_;
    GpioHandler* gpio_handler_;
    UController* u_controller_;
};

#endif