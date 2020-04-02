cmake_minimum_required(VERSION 2.8.3)
project(main)

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

set(CMAKE_CXX_FLAGS_RELEASE "-O1")

add_compile_options(-std=c++11)

set(warnings "-Wall -Wextra")
# add_definitions(-D__print_image)
# add_definitions(-D__local)
# add_definitions(-D__extern)

include_directories(
  shared
  shared/include
  ../shared/
  ../shared/include
  ../shared/Image/include
  ../shared/Lock/include
  ../shared/GamePad/include
  ../shared/Thread/include
  ../shared/Socket/include
  ../../shared
  extern/include
  raspberry/include
  control/include
  camera/include
  client/include
)

add_library( 
  working_thread
  SHARED
  ../shared/Thread/src/WorkingThread.cpp
)
add_library( 
  thread_handler
  SHARED
  ../shared/Thread/src/ThreadHandler.cpp
)
add_library( 
  socket
  SHARED
  ../shared/Socket/src/Socket.cpp
)
add_library( 
  game_pad
  SHARED
  ../shared/GamePad/src/GamePad.cpp
)
add_library(
  image
  SHARED
  ../shared/Image/src/Image.cpp
)
add_library(
  image_rgb
  SHARED
  ../shared/Image/src/ImageRGB.cpp
)
add_dependencies(
  image_rgb
  image
)
add_library(
  image_jpeg
  SHARED
  ../shared/Image/src/ImageJPEG.cpp
)
add_library(
  lock
  SHARED
  ../shared/Lock/src/Lock.cpp
)
add_library(
  cond
  SHARED
  ../shared/Lock/src/Cond.cpp
)

add_subdirectory(extern) 
add_subdirectory(shared) 
add_subdirectory(control) 
add_subdirectory(camera)
add_subdirectory(client) 
add_subdirectory(raspberry) 

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} main.cpp)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "amd64.*|x86_64.*|AMD64.*")
target_link_libraries(
  ${PROJECT_NAME}
  communication
  control
  peripherial
  camera_handler
  game_pad_client
  working_thread
  gpio
  i2c
  atmega
  spi
  usart
  u_controller
  lock
  game_pad_instance
  socket
  game_pad
  image
  image_rgb
  image_jpeg
  client_handler
  camera_client
  camera
  cond
  thread_handler
  gpio_handler
  i2c_handler
  atmega_i2c_handler
  i2c_register_data
  -pthread
  -lrt
  -ljsoncpp
)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm.*|ARM.*)")
target_link_libraries(
  ${PROJECT_NAME}
  communication
  control
  peripherial
  camera_handler
  game_pad_client
  working_thread
  gpio
  i2c
  atmega
  spi
  usart
  u_controller
  lock
  game_pad_instance
  socket
  game_pad
  image
  image_rgb
  image_jpeg
  client_handler
  camera_client
  camera
  cond
  thread_handler
  gpio_handler
  i2c_handler
  atmega_i2c_handler
  i2c_register_data
  -pthread
  -lwiringPi
  -lrt
  -ljsoncpp
  -lraspicam 
  -ljpeg
)
endif()
