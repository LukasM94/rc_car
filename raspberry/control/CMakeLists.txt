cmake_minimum_required(VERSION 2.8.3)
project(control)

## Declare a C++ library
add_library( 
  communication
  src/communication.cpp
)
add_library( 
  i2c
  src/i2c.cpp
  src/communication.cpp
)
add_library( 
  spi
  src/spi.cpp
  src/communication.cpp
)
add_library( 
  usart
  src/usart.cpp
  src/communication.cpp
)
add_library( 
  atmega
  src/atmega.cpp
  src/i2c.cpp
  src/communication.cpp
)
add_library( 
  gpio
  src/gpio.cpp
)
add_library( control
  src/control.cpp
)
