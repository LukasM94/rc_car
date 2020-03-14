add_library(
  camera
  SHARED
  src/Camera.cpp
)
add_library( 
  camera_handler
  SHARED
  src/CameraHandler.cpp
)
add_dependencies(
  camera_handler
  working_thread
  image
  camera
)

