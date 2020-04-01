
#include <Spi.h>

Spi::Spi(const char* name) : 
    Communication(name, Communication::TYPE_SPI)
{

}

Spi::~Spi()
{

}

int Spi::write(uint8_t reg, const uint8_t* data, int length)
{
  return -1;
}

int Spi::read(uint8_t reg, uint8_t* data, int lenght)
{
  return -1;
}