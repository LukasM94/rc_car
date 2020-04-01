#ifndef GPIO_HANDLER_H
#define GPIO_HANDLER_H

#include <WorkingThread.h>

class ControlHandler;

class GpioHandler : public WorkingThread
{
  public:
    GpioHandler(ControlHandler* control_handler);
    ~GpioHandler();

    void init();
    void deinit();

    virtual void run();

    static void buttonCallback(); 
  
  private:
    GpioHandler();

    ControlHandler* control_handler_;
};

#endif