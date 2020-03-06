add_library( 
  game_pad_client
  SHARED
  src/GamePadClient.cpp
  ../../shared/src/GamePad.cpp
  ../../shared/src/Socket.cpp
)