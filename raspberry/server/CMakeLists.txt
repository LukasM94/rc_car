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

add_library( 
  xbox_controller
  src/XboxController.cpp
)
add_library( 
  socket_server
  ../shared/src/Socket.cpp
  src/Server.cpp
)
add_library( 
  gamepad
  ../shared/src/GamePad.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
  xbox_controller
  socket_server
  gamepad
  -pthread
  -ljsoncpp
)
