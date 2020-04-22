/*
 * printf.h
 *
 *  Created on: Jan 30, 2019
 *      Author: lukas
 */

#ifndef PRINTF_H_
#define PRINTF_H_

#include "Usart.h"

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')

void Printf_init(struct Usart* usart);

uint8_t Printf_print(char* fmt, ...);

#endif /* PRINTF_H_ */
