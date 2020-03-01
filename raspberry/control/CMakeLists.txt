cmake_minimum_required(VERSION 2.8.3)
project(control)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Specify additional locations of header files
include_directories(
  include
  ../../shared
)

## Declare a C++ library
add_library( COMMUNICATION
  src/communication.cpp
)
add_library( I2C
  src/i2c.cpp
  src/communication.cpp
)
add_library( SPI
  src/spi.cpp
  src/communication.cpp
)
add_library( USART
  src/usart.cpp
  src/communication.cpp
)
add_library( ATMEGA
  src/atmega.cpp
  src/i2c.cpp
  src/communication.cpp
)
add_library( GPIO
  src/gpio.cpp
)

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(${PROJECT_NAME} control.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(
  ${PROJECT_NAME}
  COMMUNICATION
  I2C
  SPI
  USART
  ATMEGA
  GPIO
  -lwiringPi
  -lrt
  -pthread
)
