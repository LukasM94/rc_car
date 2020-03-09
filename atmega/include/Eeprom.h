#ifndef EEPROM_H
#define EEPROM_H


#define EEPROM_OFFSET_ADDRESS_A 0x00
#define EEPROM_OFFSET_ADDRESS_B 0x01
#define EEPROM_CONTROL_REGISTER_ADDRESS 0x10

uint8_t readEEPROM(uint8_t address);
void writeEEPROM(uint8_t data, uint8_t address);

#endif