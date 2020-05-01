#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <avr/wdt.h>

static inline void watchdogEnable()
{
  wdt_enable(WDTO_500MS);
}

static inline void watchdogDisable()
{
  wdt_disable();
}

static inline void watchdogReset()
{
  wdt_reset();
}

#endif