
#ifndef CONFIG_H
#define CONFIG_H

#define SERVER_PORT "64213"
#define SERVER_PORT_INT 64213

#if defined(__local)
#define SERVER_IP   "127.0.0.1"
#elif defined(__extern)
// please change
#define SERVER_IP   ""
#else
#define SERVER_IP   "192.168.0.32"
#endif

#define RASPBERRY_PIN_COUNT 28

#define RASPBERRY_LED_GREEN 0
#define RASPBERRY_LED_RED   5
#define RASPBERRY_BUTTON    1
#define RASPBERRY_RESET     6

#define RASPBERRY_I2C_SDA   2
#define RASPBERRY_I2C_SCL   3

#define RASPBERRY_PWM0_0    12
#define RASPBERRY_PWM1      13

#define RASPBERRY_USART_TXD 14
#define RASPBERRY_USART_RXD 15

#define RASPBERRY_PWM0_1    18

#define SERVER_SEND_DATA    20000 //us

#define XBOX_CONTROLLER_PATH "/dev/input/js0"

#define COMMON_PACKAGE_SIZE 4096

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
