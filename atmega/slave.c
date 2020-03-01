
#include "config.h"
#include "Usart.h"
#include "Printf.h"
#include "I2cSlave.h"
#include <string.h>
#include <i2c_protocol.h>

//---------------------------------------------------------------------
struct Usart usart;
volatile uint8_t buffer[256];
volatile uint8_t buffer_length;
volatile uint8_t flag;
volatile uint8_t received_register;

//---------------------------------------------------------------------
void initUsart();
void initLed();
void initI2c();

void receiveFunction(uint8_t* data, uint8_t length, uint8_t reg);
void requestFunction();

//---------------------------------------------------------------------
int main()
{
  initUsart();
  initLed();
  initI2c();
  Printf_print("slave\n");

  sei();

  while (1)
  {
    if (flag)
    {
      flag = 0;
      const char* register_name = getNameOfRegister(received_register);
      // Printf_print("register %d\n", received_register);
      Printf_print("register %s\n", register_name);
      Printf_print("%s\n", (char*)buffer);
      for (int i = 0; i < 256; ++i)
      {
        buffer[i] = 0;
      }
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
void receiveFunction(uint8_t* data, uint8_t length, uint8_t reg)
{
  if (length > 2)
  {
    ++data;
    --length;
  }
  buffer_length     = length;
  received_register = reg;
  for (int i = 0; i < length; ++i)
  {
    buffer[i] = data[i];
  }
  flag = 1;
}

//---------------------------------------------------------------------
void requestFunction()
{
}