#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

typedef uint8_t boolean;
#define false 0
#define true  1

#define LED_PORT    PORTB
#define LED_DDR     DDRB
#define LED_PIN     PB4
#define LED_ON      LED_PORT |= (1 << LED_PIN)
#define LED_OFF     LED_PORT &= ~(1 << LED_PIN)
#define LED_TOOGLE  LED_PORT ^= (1 << LED_PIN)

#endif // CONFIG_H