
#include <config.h>
#include <Usart.h>
#include <Printf.h>
#include <Timer.h>
#include <Pwm.h>
#include <I2cRegister.h>
#include <string.h>

//---------------------------------------------------------------------
struct Usart       usart;
struct I2cRegister i2c_register;
struct Pwm         pwm;

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
    i2c_register.update(&i2c_register);
    pwm.update(&pwm);
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
  Pwm_ctor(&pwm);
}
