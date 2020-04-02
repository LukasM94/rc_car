#ifndef ATMEGA_I2C_HANDLER_H
#define ATMEGA_I2C_HANDLER_H

#include <I2cHandler.h>

class AtmegaI2cHandler : public I2cHandler
{
  public:
    AtmegaI2cHandler(ControlHandler* control_handler);
    ~AtmegaI2cHandler();

    virtual void run();

  protected:
    UController* u_controller_;

  private:
};

#endif