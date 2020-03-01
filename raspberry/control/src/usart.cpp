
#include <usart.h>

Usart::Usart(const char* name) : 
    Communication(name, Communication::TYPE_USART)
{

}

Usart::~Usart()
{

}

int Usart::write(uint8_t reg, const uint8_t* data, int length)
{
  return -1;
}

int Usart::read(uint8_t reg, uint8_t* data, int lenght)
{
  return -1;
}