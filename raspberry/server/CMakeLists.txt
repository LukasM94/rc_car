cmake_minimum_required(VERSION 2.8.3)
project(server)

if (NOT CONFIGURED_ONCE)
    set(CMAKE_CXX_FLAGS "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
    set(CMAKE_C_FLAGS   "${warnings}"
        CACHE STRING "Flags used by the compiler during all build types." FORCE)
endif()

add_compile_options(-std=c++11)

set(__cplusplus 1)

include_directories(
  include
  shared
  ../shared/include
)

set(warnings "-Wall -Wextra")

add_executable(${PROJECT_NAME} server.cpp)

# shared
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

# this project
add_library( 
  xbox_controller
  SHARED
  src/XboxController.cpp
)
add_dependencies(
  xbox_controller
  gamepad
)
add_library( 
  server_handler
  SHARED
  src/ServerHandler.cpp
)
add_dependencies(
  server_handler
  socket
  working_thread
)
add_library(
  xc_service
  SHARED
  src/XboxControllerService.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  xbox_controller
  server_handler
  gamepad
  socket
  working_thread
  lock
  xc_service
  -pthread
  -ljsoncpp
)
