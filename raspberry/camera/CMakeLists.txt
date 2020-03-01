cmake_minimum_required(VERSION 2.8.3)
project(camera)

## Compile as C11, supported in ROS Kinetic and newer
add_compile_options(-std=c11)

## Specify additional locations of header files
include_directories(
  include
  ../shared
  ../../shared
)

## Declare a C++ library

## Declare a C++ executable
## With catkin_make all packages are built within a single CMake context
## The recommended prefix ensures that target names across packages don't collide
add_executable(${PROJECT_NAME} camera.c)

## Specify libraries to link a library or executable target against
target_link_libraries(
  ${PROJECT_NAME}
  -lwiringPi
  -lrt
  -pthread
)
