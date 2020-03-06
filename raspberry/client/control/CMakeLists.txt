cmake_minimum_required(VERSION 2.8.3)
project(control)

add_library( 
  control
  src/Control.cpp
  src/ControlHandler.cpp
  ../u_controller/shared/src/UController.cpp
  ../u_controller/shared/src/Usart.cpp
  ../u_controller/shared/src/Spi.cpp
  ../u_controller/shared/src/I2c.cpp
  ../u_controller/shared/src/Communication.cpp
)
# add_dependencies(
#   control
#   control_handler
#   u_controller
#   usart
#   spi
#   i2c
#   communication
# )
add_library( 
  control_handler
  src/ControlHandler.cpp
)
