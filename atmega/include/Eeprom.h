#ifndef EEPROM_H
#define EEPROM_H

uint8_t readEEPROM(uint8_t address);
void writeEEPROM(uint8_t data, uint8_t address);

#endif