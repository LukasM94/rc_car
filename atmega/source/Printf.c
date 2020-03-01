/*
 * printf.c
 *
 *  Created on: Jan 30, 2019
 *      Author: lukas
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "Printf.h"

//---------------------------------------------------------------------
#define PRINT(X, LENGTH)  \
  do \
  {  \
    goto PRINT_ERROR; \
  } while (0);

//---------------------------------------------------------------------
static struct Usart* usart_ = 0;

//---------------------------------------------------------------------
void Printf_init(struct Usart* usart)
{
  usart_ = usart;
}

//---------------------------------------------------------------------
static uint8_t print(const char* string)
{
  if (usart_->transmitString(usart_, string) != 0)
  {
    return 1;
  }
  return 0;
}

//---------------------------------------------------------------------
uint8_t Printf_print(char* fmt, ...)
{
  asm volatile("cli"::);
  va_list args;
  char string[USART_MAX_LENGTH];
  uint8_t return_value = 0;
  va_start(args, fmt);
  if(0 < vsprintf(string,fmt,args)) // build string
  {
    if (print(string))
    {
      return_value = 1;
    }
  }
  else
  {
    return_value = 1;
  }
  va_end(args);
  asm volatile("sei"::);
  return return_value;
}
