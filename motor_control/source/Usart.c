/*
 * usart.c
 *
 * Created: 25.02.2020
 *  Author: Lukas
 */ 

#include "Usart.h"
#include <avr/io.h>

//---------------------------------------------------------------------
__attribute__((unused))static void initUsart(struct Usart* this, uint16_t baut)
{
  uint16_t register_ubrr = UBRRn(baut);
  //Set baud rate 
  UBRR0H = (register_ubrr >> 8) & 0xff;
  UBRR0L = register_ubrr & 0xff;
  //Enable receiver and transmitter 
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  // Set frame format: 8data, 2stop bit, odd parity
  UCSR0C = (1 << USBS0)  | 
           (1 << UCSZ00) | (1 << UCSZ01) |
           (1 << UPM00)  | (1 << UPM01);
}

//---------------------------------------------------------------------
struct Usart* Usart_ctor(struct Usart* this, uint8_t port, uint16_t baut)
{
  Usart_init(this);
  initUsart(this, baut);
  return this;
}

//---------------------------------------------------------------------
int Usart_transmit(struct Usart* this, uint8_t data)
{
  long timeout = 0xffffff;
  // Wait for empty transmit buffer 
  while (!(UCSR0A & (1<<UDRE0)))
  {
    if (--timeout <= 0)
    {
      return -1;
    }
  }
  
  // Put data into buffer, sends the data 
  UDR0 = data;
  return 0;
}

//---------------------------------------------------------------------
int Usart_transmitString(struct Usart* this, const char* string)
{
  const char* c = string;
  int i = 0;
  while (*c != 0 && i < USART_MAX_LENGTH)
  {
    int ret;
    if ((ret = Usart_transmit(this, (uint8_t)*c)) != 0)
    {
      return ret;
    }
    ++i;
    ++c;
  }
  return 0;
}