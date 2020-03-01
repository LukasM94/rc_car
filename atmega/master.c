
#include "config.h"
#include "Usart.h"
#include "Printf.h"
#include "I2cMaster.h"

//---------------------------------------------------------------------
struct Usart usart;

//---------------------------------------------------------------------
void initUsart();
void initLed();
void initI2c();

//---------------------------------------------------------------------
int main()
{
  initUsart();
  initLed();
  initI2c();
  Printf_print("master\n");

  while (1)
  {
    uint8_t c[6] = "hallo";
    uint8_t ret;
    uint8_t position = 0x20;
    ret = i2cWriteReg((ADDRESS << 1), position, c, 6);
    Printf_print("register 0x%x\n", position);
    Printf_print("write    0x%x\n", ADDRESS);
    Printf_print("return   %d\n", ret);
    LED_TOOGLE;
    _delay_ms(500);
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
  i2cInit();
}
