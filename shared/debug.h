#pragma once

#include <stdio.h>

enum AnsiColor
{
  Ansi_Red = 31,
  Ansi_Green = 32,
  Ansi_Yellow = 33,
  Ansi_Blue = 34,
  Ansi_Magenta = 35,
  Ansi_Cyan = 36,
  Ansi_White = 37,
};

#define OUTPUT_ENABLED 0x80000000
#define OUTPUT_ADVANCED 0x70000000
#define OUTPUT_FLAGS (OUTPUT_ENABLED | OUTPUT_ADVANCED)

#define DEBUG_FORMAT_STRING "\033[1;%zum[%-11s]\033[0;39m"
#define COLOR_PARAM(flag) (flag & ~OUTPUT_FLAGS), #flag

#define debug(flag, ...) do { if (flag & OUTPUT_ENABLED) { printf(DEBUG_FORMAT_STRING, COLOR_PARAM(flag)); printf(__VA_ARGS__); } } while (0)

const size_t MAIN        = Ansi_Blue    | OUTPUT_ENABLED;
const size_t CONTROL     = Ansi_Green   | OUTPUT_ENABLED;
const size_t GPIO        = Ansi_Yellow  | OUTPUT_ENABLED;
const size_t I2C         = Ansi_White   | OUTPUT_ENABLED;
const size_t ATMEGA      = Ansi_Cyan    | OUTPUT_ENABLED;
const size_t ERROR       = Ansi_Red     | OUTPUT_ENABLED;
const size_t COM         = Ansi_Magenta | OUTPUT_ENABLED;