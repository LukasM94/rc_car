add_library(
  client_handler
  SHARED
  src/ClientHandler.cpp
)
add_dependencies(
  client_handler
  socket
  working_thread
)
add_library(
  camera_client
  SHARED
  src/CameraClient.cpp
)
add_dependencies(
  camera_client
  working_thread
  camera_handler
)
add_library( 
  game_pad_client
  SHARED
  src/GamePadClient.cpp
)
add_dependencies(
  game_pad_client
  game_pad
)
add_library( 
  game_pad_instance
  SHARED
  src/GamePadInstance.cpp
)
add_dependencies(
  game_pad_instance
  game_pad_client
  socket
  game_pad
)