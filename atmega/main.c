
#include "config.h"
#include "Usart.h"
#include "Printf.h"
#include "Timer.h"
#include "Pwm.h"
#include "I2cRegister.h"
#include <string.h>

//---------------------------------------------------------------------
struct Usart       usart;
struct I2cRegister i2c_register;
struct Pwm         pwm;

uint32_t time_threshold;
int8_t   pwm_ocra_offset;
int8_t   pwm_ocrb_offset;

//---------------------------------------------------------------------
void initUsart();
void initLed();
void initI2c();
void initPwm();

//---------------------------------------------------------------------
int main()
{
  cli();
  initUsart();
  initLed();
  initI2c();
  initPwm();
  sei();

  Printf_print("main: Start\n");
  Printf_print("main: print eeprom\n");
  i2c_register.printEEPROMRegisters(&i2c_register);

  while (1)
  {
    i2c_register.run(&i2c_register);
  }
}

//---------------------------------------------------------------------
void initUsart()
{
  Usart_ctor(&usart, 0, 9600);
  Printf_init(&usart);
}

//---------------------------------------------------------------------
void initLed()
{
  LED_DDR |= (1 << LED_PIN);
}

//---------------------------------------------------------------------
void initI2c()
{
  I2cRegister_ctor(&i2c_register);
}

//---------------------------------------------------------------------
void initPwm()
{
  int8_t motor_offset = i2c_register.readMotorOffset(&i2c_register);
  int8_t servo_offset = i2c_register.readServoOffset(&i2c_register);
  Pwm_ctor(&pwm, motor_offset, servo_offset);
}
