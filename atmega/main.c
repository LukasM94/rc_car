
#include "config.h"
#include "Usart.h"
#include "Printf.h"
#include "Timer.h"
#include "Pwm.h"
#include "I2cRegister.h"
#include <string.h>

//---------------------------------------------------------------------
#define BUFFER_SIZE          256
#define CR_PWM_RUNNING       0x00
#define CR_SET_PWM_RUNNING   do { control_register |= (1 << CR_PWM_RUNNING); } while(0)
#define CR_RESET_PWM_RUNNING do { control_register &= ~(1 << CR_PWM_RUNNING); } while(0)
#define CR_GET_PWM_RUNNING   (control_register & (1 << CR_PWM_RUNNING))

//---------------------------------------------------------------------
struct Usart       usart;
struct I2cRegister i2c_register;
struct Pwm         pwm;

uint32_t time_threshold;
int8_t   pwm_ocra_offset;
int8_t   pwm_ocrb_offset;

volatile uint8_t  i2c_revc_data[BUFFER_SIZE];

volatile uint8_t  flag              = 0;
volatile uint8_t  swapped_flag      = 0;
volatile uint8_t  i2c_recv_length   = 0;
volatile uint8_t  i2c_recv_register = 0;
volatile uint32_t time_last_i2c     = 0;

//---------------------------------------------------------------------
void initUsart();
void initLed();
void initI2c();
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
  // initPwm();
  sei();

  Printf_print("main: Start\n");
  Printf_print("main: print eeprom\n");
  i2c_register.printEEPROMRegisters(&i2c_register);

  while (1)
  {
    cli();
    swapped_flag = flag;
    flag         = 0;
    sei();
    if (swapped_flag)
    {
      const char* register_name = i2c_register.getNameOfRegister(i2c_recv_register);
      Printf_print("%s\n", register_name);
      Printf_print("data <%d>\n", i2c_revc_data[0]);
      i2c_register.write(&i2c_register, i2c_revc_data[0], i2c_recv_register);
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
  I2cRegister_ctor(&i2c_register);
  i2c_register.initSlave(&i2c_register, receiveFunction, requestFunction);
}

//---------------------------------------------------------------------
void initPwm()
{
  int8_t motor_offset = i2c_register.readMotorOffset(&i2c_register);
  int8_t servo_offset = i2c_register.readServoOffset(&i2c_register);
  Pwm_ctor(&pwm, motor_offset, servo_offset);
}

//---------------------------------------------------------------------
void receiveFunction(uint8_t* data, uint8_t length, uint8_t reg)
{
  LED_TOOGLE;
  if (length > 2)
  {
    ++data;
    --length;
  }
  i2c_recv_length   = length;
  i2c_recv_register = reg;
  for (int i = 0; (i < length) && (i < BUFFER_SIZE); ++i)
  {
    i2c_revc_data[i] = data[i];
  }
  flag = 1;
  time_last_i2c = 0;
}

//---------------------------------------------------------------------
void requestFunction()
{
}
