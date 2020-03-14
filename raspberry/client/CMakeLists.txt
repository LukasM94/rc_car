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
# add_definitions(-D__print_image)
# add_definitions(-D__local)
# add_definitions(-D__extern)

include_directories(
  shared/include
  ../shared/
  ../shared/include
  ../../shared
  extern/include
  raspberry/include
  extern_control/include
  camera/include
  client/include
)

add_library( 
  working_thread
  SHARED
  ../shared/src/WorkingThread.cpp
)
add_library( 
  socket
  SHARED
  ../shared/src/Socket.cpp
)
add_library( 
  game_pad
  SHARED
  ../shared/src/GamePad.cpp
)
add_library(
  image
  SHARED
  ../shared/src/Image.cpp
)
add_library(
  image_rgb
  SHARED
  ../shared/src/ImageRGB.cpp
)
add_dependencies(
  image_rgb
  image
)
add_library(
  image_jpeg
  SHARED
  ../shared/src/ImageJPEG.cpp
)
add_library(
  lock
  SHARED
  ../shared/src/Lock.cpp
)
add_library(
  cond
  SHARED
  ../shared/src/Cond.cpp
)

add_subdirectory(extern) 
add_subdirectory(shared) 
add_subdirectory(extern_control) 
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
  extern_control
  peripherial
  control
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
  -pthread
  -lrt
  -ljsoncpp
)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm.*|ARM.*)")
target_link_libraries(
  ${PROJECT_NAME}
  communication
  extern_control
  peripherial
  control
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
  -pthread
  -lwiringPi
  -lrt
  -ljsoncpp
  -lraspicam 
  -ljpeg
)
endif()
