add_library(
  image_instance
  SHARED
  src/ImageInstance.cpp
)
add_dependencies(
  image_instance
  image
)
add_library(
  game_pad_instance
  SHARED
  src/GamePadInstance.cpp
)
add_library(
  transceived_data_instance
  SHARED
  src/TransceivedDataInstance.cpp
)