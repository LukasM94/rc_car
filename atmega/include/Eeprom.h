#ifndef EEPROM_H
#define EEPROM_H

int8_t readOffsetA();
int8_t readOffsetB();
void writeOffsetA(int8_t data);
void writeOffsetB(int8_t data);

#endif