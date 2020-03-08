#include <avr/eeprom.h> 
#include <Eeprom.h>

#define EEPROM_OFFSET_ADDRESS_A 0x00
#define EEPROM_OFFSET_ADDRESS_B 0x10


int8_t readOffsetA()
{
  return (int8_t)eeprom_read_byte((const uint8_t*)EEPROM_OFFSET_ADDRESS_A);
}

int8_t readOffsetB()
{
  return (int8_t)eeprom_read_byte((const uint8_t*)EEPROM_OFFSET_ADDRESS_B);
}

void writeOffsetA(int8_t data)
{
  eeprom_write_byte((uint8_t*)EEPROM_OFFSET_ADDRESS_A, data);
}

void writeOffsetB(int8_t data)
{
  eeprom_write_byte((uint8_t*)EEPROM_OFFSET_ADDRESS_B, data);
}
