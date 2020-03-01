#include <pthread.h>
#include <sched.h>
#include <atmega.h>
#include <string.h>
#include <gpio.h>
#include <i2c_protocol.h>
#include <debug.h>

#define LED_PIN 0 // change pin number here

//--------------------------------------------------------------------
// pthread_t tid_i2c;
volatile int running = 1;
Atmega* atmega;

//--------------------------------------------------------------------
void  gpioInit();
void  i2cInit();
void  buttonCallback();

//--------------------------------------------------------------------
int main (int argc, char **argv)
{
  gpioInit();
  i2cInit();

  debug(CONTROL, "Finish with initialization\n");
  debug(CONTROL, "Start hear beat\n");

  while (running)
  {
    Gpio::instance()->heartBeat();
  }
  debug(CONTROL, "End hear beat\n");
}

//--------------------------------------------------------------------
void gpioInit()
{
  Gpio::instance()->initLed();
  Gpio::instance()->initButton(&buttonCallback);
}

//--------------------------------------------------------------------
void i2cInit()
{
  atmega = new Atmega();
}

//--------------------------------------------------------------------
void buttonCallback()
{
  debug(CONTROL, "Button pressed\n");

  int      reg   = I2C_MOTOR;
  uint16_t speed = 0x1234;
  atmega->writeI2c(reg, (const uint8_t*)&speed, 2);
}