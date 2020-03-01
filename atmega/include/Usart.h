/*
 * usart.h
 *
 * Created: 25.02.2020
 *  Author: Lukas
 */ 


#ifndef USART_H_
#define USART_H_

#include <stdio.h>

#ifndef F_CPU
#define F_CPU 16000000
#endif

#define USART_MAX_LENGTH 32

#define UBRRn(BAUD)   F_CPU/16/BAUD-1

struct Usart
{
  volatile unsigned char* ubrrh_;
  volatile unsigned char* ubrrl_;
  volatile unsigned char* ucsrb_;
  volatile unsigned char* ucsrc_;
  volatile unsigned char* ucsra_;
  volatile unsigned char* udr_;
  int (*transmit)(struct Usart* this, uint8_t data);
  int (*transmitString)(struct Usart* this, const char* string);
};

struct Usart* Usart_ctor(struct Usart* this, uint8_t port, uint16_t baut);
struct Usart* Usart_dtor(struct Usart* this);

int Usart_transmit(struct Usart* this, uint8_t data);
int Usart_transmitString(struct Usart* this, const char* string);

__attribute__((unused))static void Usart_init(struct Usart* usart)
{
  usart->transmit = &Usart_transmit;
  usart->transmitString = &Usart_transmitString;
}

#endif 