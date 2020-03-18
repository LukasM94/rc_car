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
  instances/include
  graphics/include
  server/include
  xbox/include
  shared
  ../shared/include
  ../shared/Image/include
  ../shared/Lock/include
  ../shared/GamePad/include
  ../shared/Thread/include
  ../shared/Socket/include
)

set(warnings "-Wall -Wextra")

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} main.cpp)

# shared
add_library( 
  image
  SHARED
  ../shared/Image/src/Image.cpp
)
add_library( 
  image_jpeg
  SHARED
  ../shared/Image/src/ImageJPEG.cpp
)
add_library( 
  image_rgb
  SHARED
  ../shared/Image/src/ImageRGB.cpp
)
add_library( 
  gamepad
  SHARED
  ../shared/GamePad/src/GamePad.cpp
)
add_library( 
  socket
  SHARED
  ../shared/Socket/src/Socket.cpp
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
  lock
  SHARED
  ../shared/Lock/src/Lock.cpp
)
add_library(
  cond
  SHARED
  ../shared/Lock/src/Cond.cpp
)

add_subdirectory(graphics) 
add_subdirectory(server) 
add_subdirectory(xbox) 
add_subdirectory(instances) 

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
  main_window
  thread_handler
  -pthread
  -ljsoncpp
  -ljpeg
)
