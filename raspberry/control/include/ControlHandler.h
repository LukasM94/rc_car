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
    static ControlHandler* instance();
    ~ControlHandler();

    virtual void run();

    void deinit();

  private:
    friend GpioHandler;
    friend I2cHandler;

    ControlHandler();
    static ControlHandler* instance_;
    
    ControlHandler(const ControlHandler&);

    I2cHandler*  i2c_handler_;
    GpioHandler* gpio_handler_;
};

#endif