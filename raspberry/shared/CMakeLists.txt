cmake_minimum_required(VERSION 2.8.3)
project(main)

add_library( 
  socket
  src/Socket.cpp
)
add_library( 
  game_pad
  src/GamePad.cpp
)
