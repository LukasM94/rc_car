cmake_minimum_required(VERSION 2.8.3)
project(main)

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

add_compile_options(-std=c++11)

set(warnings "-Wall -Wextra")
# add_definitions(-D__local)
# add_definitions(-D__extern)

include_directories(
  shared
  ../shared/
  ../shared/include
  ../../shared
  u_controller/atmega/include
  u_controller/shared/include
  control/include
  camera/include
  game_pad_client/include
)

add_subdirectory(u_controller) 
add_subdirectory(control) 
add_subdirectory(camera)
add_subdirectory(game_pad_client) 

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(
  ${PROJECT_NAME}
  communication
  control
  camera
  game_pad_client
  gpio
  i2c
  atmega
  spi
  usart
  u_controller
  -pthread
  -lwiringPi
  -lrt
  -ljsoncpp
)
