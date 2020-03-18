#ifndef I2C_HANDLER_H
#define I2C_HANDLER_H

#include <WorkingThread.h>

class ControlHandler;

class I2cHandler : public WorkingThread
{
  public:
    I2cHandler(ControlHandler* control_handler);
    ~I2cHandler();

    virtual void run();

    void init();
    void deinit();
  private:
    void writeI2c(uint8_t reg, const uint8_t* data, int length);

    std::atomic_uint8_t  i2c_error_;
    static const uint8_t I2C_ERROR_THRESHOLD = 5;
    static const uint8_t GAME_PAD_ERROR_THRESHOLD = 5;

    ControlHandler* control_handler_;

    enum I2C_MODE { NORMAL, OFFSET };

    static const int8_t THRESHOLD_FOR_JOYSTICK = 50;
};

#endif