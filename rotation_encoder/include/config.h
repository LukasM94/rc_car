#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PORT    PORTB
#define LED_DDR     DDRB
#define LED_PIN     PB1
#define LED_ON      LED_PORT |= (1 << LED_PIN)
#define LED_OFF     LED_PORT &= ~(1 << LED_PIN)
#define LED_TOOGLE  LED_PORT ^= (1 << LED_PIN)

#define LIGHT_BARRIER_PORT PORTB 
#define LIGHT_BARRIER_PIN  PINB 
#define LIGHT_BARRIER_DDR  DDRB 
#define LIGHT_BARRIER0_PIN PB3
#define LIGHT_BARRIER1_PIN PB4
#define LIGHT_BARRIER0     (LIGHT_BARRIER_PIN & (1 << LIGHT_BARRIER0_PIN)) 
#define LIGHT_BARRIER1     (LIGHT_BARRIER_PIN & (1 << LIGHT_BARRIER1_PIN)) 

#endif // CONFIG_H