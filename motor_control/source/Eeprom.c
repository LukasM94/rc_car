#include <avr/eeprom.h> 
#include <Eeprom.h>

uint8_t readEEPROM(uint8_t address)
{
  return (uint8_t)eeprom_read_byte((const uint8_t*)address);
}

void writeEEPROM(uint8_t data, uint8_t address)
{
  eeprom_write_byte((uint8_t*)address, data);
}