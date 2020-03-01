
#ifndef CONFIG_H
#define CONFIG_H

#define RASPBERRY_PIN_COUNT 28

#define RASPBERRY_I2C_SDA   2
#define RASPBERRY_I2C_SCL   3

#define RASPBERRY_PWM0_0    12
#define RASPBERRY_PWM1      13

#define RASPBERRY_USART_TXD 14
#define RASPBERRY_USART_RXD 15

#define RASPBERRY_PWM0_1    18

#include <stdio.h>

static size_t gpios[RASPBERRY_PIN_COUNT];

static inline int gpioTestAndSet(unsigned int pin)
{
  size_t value = 1;
  value = __atomic_exchange_n((size_t*)(gpios + pin), value, __ATOMIC_RELAXED);
  return value != 0;
}

static inline int gpioTestAndUnset(unsigned int pin)
{
  size_t value = 0;
  value = __atomic_exchange_n((size_t*)(gpios + pin), value, __ATOMIC_RELAXED);
  return value == 0;
}

#endif