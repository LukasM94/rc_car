
#include "config.h"
#include "Usart.h"
#include "Printf.h"
#include "Timer.h"
#include "I2cSlave.h"
#include "Pwm.h"
#include "Eeprom.h"
#include <string.h>
#include <com_config.h>

//---------------------------------------------------------------------
#define BUFFER_SIZE          256
#define CR_PWM_RUNNING       0x00
#define CR_SET_PWM_RUNNING   do { control_register |= (1 << CR_PWM_RUNNING); } while(0)
#define CR_RESET_PWM_RUNNING do { control_register &= ~(1 << CR_PWM_RUNNING); } while(0)
#define CR_GET_PWM_RUNNING   (control_register & (1 << CR_PWM_RUNNING))

//---------------------------------------------------------------------
struct Usart usart;

uint32_t time_threshold;
int8_t   pwm_ocra_offset;
int8_t   pwm_ocrb_offset;

volatile uint8_t  buffer[BUFFER_SIZE];

volatile uint8_t  flag              = 0;
volatile uint8_t  swapped_flag      = 0;
volatile uint8_t  buffer_length     = 0;
volatile uint8_t  received_register = 0;
volatile uint32_t time_last_i2c     = 0;

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
  initUsart();
  initLed();
  initI2c();
  initTimer();
  initPwm();
  sei();

  Printf_print("main: start\n");

  while (1)
  {
    cli();
    swapped_flag = flag;
    flag         = 0;
    sei();
    if (flag)
    {
      const char* register_name = getNameOfRegister(received_register);
      Printf_print("Received register %s\n", register_name);
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
  i2cSlaveInit(I2C_ADDRESS);
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
