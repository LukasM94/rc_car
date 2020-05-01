#ifndef WATCHDOG_H
#define WATCHDOG_H

#include <avr/wdt.h>

inline void watchdogEnable()
{
  wdt_enable(WDTO_1S);
}

inline void watchdogDisable()
{
  wdt_disable();
}

inline void watchdogReset()
{
  wdt_reset();
}

#endif