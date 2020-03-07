
#include "config.h"
#include "Usart.h"
#include "Printf.h"
#include "Timer.h"
#include "I2cSlave.h"
#include "Pwm.h"
#include <string.h>
#include <com_config.h>

#define BUFFER_SIZE 256

//---------------------------------------------------------------------
struct Usart usart;

volatile uint8_t  buffer[BUFFER_SIZE];
volatile uint8_t  buffer_length;
volatile uint8_t  flag;
volatile uint8_t  received_register;
volatile uint32_t time_last_i2c;

uint32_t time_threshold;

//---------------------------------------------------------------------
void initUsart();
void initLed();
void initI2c();
void initTimer();
void initPwm();

void receiveFunction(uint8_t* data, uint8_t length, uint8_t reg);
void requestFunction();

void timer();

//---------------------------------------------------------------------
int main()
{
  cli();

  uint8_t old_flag;
  uint8_t lost_i2c;

  initUsart();
  initLed();
  initI2c();
  initTimer();
  initPwm();
  Printf_print("main: slave\n");

  sei();

  while (1)
  {
    cli();
    old_flag = flag;
    flag     = 0;
    
    lost_i2c = time_last_i2c > time_threshold ? 1 : 0;
    sei();
    if (old_flag)
    {
      const char* register_name = getNameOfRegister(received_register);
      int8_t value = (int8_t)buffer[received_register];
      Printf_print("main: <%s> <%d>\n", register_name, value);
      if (received_register == I2C_MOTOR)
      {
        pwmChangePulseOfOCRA(value);
      }
      else if (received_register == I2C_SERVO)
      {
        pwmChangePulseOfOCRB(value);
      }
    }
    if (lost_i2c)
    {
      Printf_print("main: lost i2c connection\n");
    }
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
  i2cSlaveSetCallbacks(receiveFunction, requestFunction);
  i2cSlaveInit(ADDRESS);
}

//---------------------------------------------------------------------
void initTimer()
{
  time_threshold = (volatile uint32_t)((((F_CPU / PRESCALE) * I2C_DEAD_TIME) / 1000) / 256); 

  timerInit();
  timerSetCallbacks(timer);
  timerStart();
}

//---------------------------------------------------------------------
void initPwm()
{
  pwmInit();
}

//---------------------------------------------------------------------
void receiveFunction(uint8_t* data, uint8_t length, uint8_t reg)
{
  if (length > 2)
  {
    ++data;
    --length;
  }
  buffer_length     = length;
  received_register = reg;
  for (int i = 0; (i < length) && (i + reg < BUFFER_SIZE); ++i)
  {
    buffer[i + reg] = data[i];
  }
  flag = 1;
  time_last_i2c = 0;
}

//---------------------------------------------------------------------
void requestFunction()
{
}

//---------------------------------------------------------------------
void timer()
{
  ++time_last_i2c;
}