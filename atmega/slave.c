
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

uint8_t pwm_running;
int8_t  pwm_ocra_offset;
int8_t  pwm_ocrb_offset;

//---------------------------------------------------------------------
void initUsart();
void initLed();
void initResetPin();
void initI2c();
void initTimer();
void initPwm();

void receiveFunction(uint8_t* data, uint8_t length, uint8_t reg);
void requestFunction();

void timer();

void changeControlRegister(uint8_t value);
void changePwmOffset(uint8_t value);

//---------------------------------------------------------------------
int main()
{
  cli();

  uint8_t old_flag;
  uint8_t lost_i2c;

  initUsart();
  initLed();
  initResetPin();
  initI2c();
  initTimer();
  initPwm();
  Printf_print("main: slave\n");
  // pwmStart();

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
      switch (received_register)
      {
        case I2C_MOTOR:
          pwmChangePulseOfOCRA(value);
          break;
        case I2C_SERVO:
          pwmChangePulseOfOCRB(value);
          break;
        case I2C_CONTROL_REGISTER:
          changeControlRegister(value);
          break;
        case I2C_CHANGE_OFFSET:
          changePwmOffset(value);
          break;
        default:
          Printf_print("Not used register %d\n", received_register);
          break;
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
void initResetPin()
{
  RESET_DDR |= (1 << RESET_PIN);
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

//---------------------------------------------------------------------
void changeControlRegister(uint8_t value)
{
  uint8_t failure = 0;
  cli();
  switch (value)
  {
    case I2C_CONTROL_REGISTER_CHANGE_PWM_RUNNING:
      if (pwm_running)
      {
        pwm_running = 0;
        pwmStop();
      }
      else
      {
        pwm_running = 1;
        pwmStart();
      }
      break;
    case I2C_CONTROL_REGISTER_RESET:
      Printf_print("atmega gets reset\n");
      RESET_ATMEGA;
      break;
    default:
      failure = 1;
      break;
  }
  sei();
  if (failure == 1)
  {
    Printf_print("changeControlRegister: %d\n", value);
  }
}

//---------------------------------------------------------------------
void changePwmOffset(uint8_t value)
{
  cli();
  switch (value)
  {
    case I2C_MOTOR_OFFSET_INCREMENT:
      (pwm_ocra_offset < 32) ? ++pwm_ocra_offset : 0;
      pwmChangePulseOfOCRA(0);
      break;
    case I2C_MOTOR_OFFSET_DECREMENT:
      (pwm_ocra_offset > -32) ? --pwm_ocra_offset : 0;
      pwmChangePulseOfOCRA(0);
      break;
    case I2C_SERVO_OFFSET_INCREMENT:
      (pwm_ocrb_offset < 32) ? ++pwm_ocrb_offset : 0;
      pwmChangePulseOfOCRB(0);
      break;
    case I2C_SERVO_OFFSET_DECREMENT:
      (pwm_ocrb_offset > -32) ? --pwm_ocrb_offset : 0;
      pwmChangePulseOfOCRB(0);
      break;
    default:
      break;
  }
  sei();
  Printf_print("changeControlRegister: ofa %d\n", pwm_ocra_offset);
  Printf_print("changeControlRegister: ofb %d\n", pwm_ocrb_offset);
}
