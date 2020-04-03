#ifndef ATMEGA_I2C_HANDLER_H
#define ATMEGA_I2C_HANDLER_H

#include <I2cHandler.h>

class I2cRegisterData;

class AtmegaI2cHandler : public I2cHandler
{
  public:
    AtmegaI2cHandler(ControlHandler* control_handler);
    ~AtmegaI2cHandler();

    virtual void run();
    virtual void init();
    virtual void deinit();

  protected:
    virtual void writeI2c(uint8_t reg, const uint8_t* data, int length);

    I2cRegisterData* i2c_register_data_;
    
    static const unsigned int I2C_HANDLER_NOT_CONNECTED_TRY_AGAIN_SLEEP_TIME = 2;
};

#endif