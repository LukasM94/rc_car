cmake_minimum_required(VERSION 2.8.3)
project(main)

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

add_compile_options(-std=c++11)

set(__cplusplus 1)

include_directories(
  graphics/include
  server/include
  xbox/include
  shared
  ../shared/include
)

set(warnings "-Wall -Wextra")

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} main.cpp)

# shared
add_library( 
  image
  SHARED
  ../shared/src/Image.cpp
)
add_library( 
  image_jpeg
  SHARED
  ../shared/src/ImageJPEG.cpp
)
add_library( 
  image_rgb
  SHARED
  ../shared/src/ImageRGB.cpp
)
add_library( 
  gamepad
  SHARED
  ../shared/src/GamePad.cpp
)
add_library( 
  socket
  SHARED
  ../shared/src/Socket.cpp
)
add_library(
  working_thread
  SHARED
  ../shared/src/WorkingThread.cpp
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

add_subdirectory(graphics) 
add_subdirectory(server) 
add_subdirectory(xbox) 

target_link_libraries(
  ${PROJECT_NAME}
  xbox_controller
  server_handler
  gamepad
  socket
  working_thread
  lock
  xc_service
  camera_service
  image
  image_jpeg
  image_rgb
  graphics
  image_instance
  cond
  -pthread
  -ljsoncpp
  -ljpeg
)
