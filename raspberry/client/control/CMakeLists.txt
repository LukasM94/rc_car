cmake_minimum_required(VERSION 2.8.3)
project(control)

## Declare a C++ library
add_library( 
  communication
  src/Communication.cpp
)
add_library( 
  i2c
  src/I2c.cpp
  src/Communication.cpp
)
add_library( 
  spi
  src/Spi.cpp
  src/Communication.cpp
)
add_library( 
  usart
  src/Usart.cpp
  src/Communication.cpp
)
add_library( 
  atmega
  src/Atmega.cpp
  src/I2c.cpp
  src/Communication.cpp
)
add_library( 
  gpio
  src/Gpio.cpp
)
add_library( control
  src/Control.cpp
)
