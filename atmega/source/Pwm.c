
#include "Pwm.h"
#include <avr/io.h>
#include <stdio.h>

#define PWM_TOP 4999

//---------------------------------------------------------------------
static uint16_t pwm_middle;
__attribute__((unused))static uint16_t pwm_border_under;
__attribute__((unused))static uint16_t pwm_border_up;

//---------------------------------------------------------------------
static void pwmChangeOCRA(uint16_t new_ocra);
static void pwmChangeOCRB(uint16_t new_ocrb);
static void pwmChangeOCR(volatile uint8_t* ORC1H, volatile uint8_t* ORC1L, uint16_t new_ocra);
static void pwmChangePulseOfOCR(volatile uint8_t* ORC1H, volatile uint8_t* ORC1L, uint16_t pulse);

//---------------------------------------------------------------------
extern int8_t pwm_ocra_offset;
extern int8_t pwm_ocrb_offset;

//---------------------------------------------------------------------
void pwmInit()
{
  TCCR1A = (1 << WGM11);
  TCCR1B = (1 << WGM12) | (1 << WGM13) | (1 << CS10) | (1 << CS11);
  
  ICR1H = (PWM_TOP >> 8) & 0xff;
  ICR1L = PWM_TOP & 0xff;
  
  //  * 7.5 / 100
  //  * 5   / 100
  //  * 10  / 100
  pwm_middle       = (PWM_TOP * 3) / 40;
  // pwm_border_under = PWM_TOP / 20;
  // pwm_border_up    = PWM_TOP / 10;
  
  pwmChangeOCRA(pwm_middle);
  pwmChangeOCRB(pwm_middle);
  
  DDRB |= (1 << PB1);
  DDRB |= (1 << PB2);
}

//---------------------------------------------------------------------
void pwmStart()
{
  TCCR1A |= (1 << COM1A1) | (1 << COM1B1);
}

//---------------------------------------------------------------------
void pwmStop()
{
  TCCR1A &= ~((1 << COM1A1) | (1 << COM1B1));
}

//---------------------------------------------------------------------
void pwmChangeOCRA(uint16_t new_ocra)
{
  pwmChangeOCR(&OCR1AH, &OCR1AL, new_ocra);
}

//---------------------------------------------------------------------
void pwmChangeOCRB(uint16_t new_ocrb)
{
  pwmChangeOCR(&OCR1BH, &OCR1BL, new_ocrb);
}

//---------------------------------------------------------------------
void pwmChangeOCR(volatile uint8_t* ORC1H, volatile uint8_t* ORC1L, uint16_t new_ocra)
{
  *ORC1H = (new_ocra >> 8) & 0xff;
  *ORC1L = new_ocra & 0xff;
}

//---------------------------------------------------------------------
void pwmChangePulseOfOCR(volatile uint8_t* ORC1H, volatile uint8_t* ORC1L, uint16_t pulse)
{
  int16_t new_ocra = (int16_t)pwm_middle + pulse;
  pwmChangeOCR(ORC1H, ORC1L, (uint16_t)new_ocra);
}

//---------------------------------------------------------------------
void pwmChangePulseOfOCRA(int8_t pulse)
{
  int16_t new_pulse = (int16_t)pulse + pwm_ocra_offset;
  pwmChangePulseOfOCR(&OCR1AH, &OCR1AL, new_pulse);
}

//---------------------------------------------------------------------
void pwmChangePulseOfOCRB(int8_t pulse)
{
  int16_t new_pulse = (int16_t)pulse + pwm_ocrb_offset;
  pwmChangePulseOfOCR(&OCR1BH, &OCR1BL, new_pulse);
}
