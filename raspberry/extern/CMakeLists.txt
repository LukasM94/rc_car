add_library(
  u_controller
  SHARED
  src/UController.cpp
)
add_dependencies(
  u_controller
  usart
  spi
  i2c
  communication
)
add_library( 
  atmega
  SHARED
  src/Atmega.cpp
)
add_dependencies(
  atmega
  u_controller
  usart
  spi
  i2c
  communication
)
add_library(
  peripherial
  SHARED
  src/Peripherial.cpp
)
add_dependencies(
  peripherial
  gpio
)


