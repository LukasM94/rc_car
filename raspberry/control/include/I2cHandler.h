#ifndef I2C_HANDLER_H
#define I2C_HANDLER_H

#include <WorkingThread.h>

class ControlHandler;
class UController;

class I2cHandler : public WorkingThread
{
  public:
    I2cHandler(ControlHandler* control_handler);
    ~I2cHandler();

    virtual void run() = 0;
    virtual void init() = 0;
    virtual void deinit() = 0;
  
  protected:

    virtual void writeI2c(uint8_t reg, const uint8_t* data, int length) = 0;

    std::atomic_uint8_t  i2c_error_;
    static const uint8_t I2C_ERROR_THRESHOLD = 5;

    ControlHandler* control_handler_;
    union 
    {
      UController* u_controller_;
      struct 
      {
        UController* u_controller_;
        size_t       count_;
      }* u_controllers_;
    } controller_;
};

#endif