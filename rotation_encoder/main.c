
#include <config.h>
#include <Usart.h>
#include <Printf.h>

//---------------------------------------------------------------------
struct Usart       usart;

//---------------------------------------------------------------------
void initUsart();

//---------------------------------------------------------------------
int main()
{
  cli();
  initUsart();
  sei();

  Printf_print("main: Start\n");

  while (1)
  {

  }
}

//---------------------------------------------------------------------
void initUsart()
{
  Usart_ctor(&usart, 0, 9600);
  Printf_init(&usart);
}
