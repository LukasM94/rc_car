cmake_minimum_required(VERSION 2.8.3)
project(main)

add_library( 
  game_pad_client
  src/GamePadClient.cpp
  ../../shared/src/Socket.cpp
  ../../shared/src/GamePad.cpp
)
add_library( 
  game_pad
  ../../shared/src/GamePad.cpp
)
