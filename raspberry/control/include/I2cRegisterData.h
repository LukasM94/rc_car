#ifndef I2C_REGISTER_DATA_H
#define I2C_REGISTER_DATA_H

#include <stdint.h>

class GamePad;

class I2cRegisterData
{
  public:
    I2cRegisterData(int8_t motor_offset, int8_t servo_offset);
    ~I2cRegisterData();

    void refreshData(GamePad* game_pad);
    void nextState();

  private:
    I2cRegisterData();
    
    enum I2C_MODE { NORMAL, OFFSET };

    // output variables
    int8_t  motor_;
    int8_t  servo_;
    int8_t  motor_offset_;
    int8_t  servo_offset_;
    uint8_t status_register_;
    uint8_t control_register_;

    // input variables
    bool   start_button_prev_;
    bool   select_button_prev_;
    int8_t y_axis_prev_;
    int8_t x_axis_prev_;
    bool   start_button_;
    bool   select_button_;
    int8_t y_axis_;
    int8_t x_axis_;

    // state variables
    enum I2C_MODE mode_;

    static const int8_t THRESHOLD_FOR_JOYSTICK = 50;
    static const int8_t MAX_OFFSET             = 50;
};

#endif