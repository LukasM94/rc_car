
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets Gui Core REQUIRED)

add_library(
  status_display
  SHARED
  src/StatusDisplay.cpp
)
add_library(
  video_display
  SHARED
  src/VideoDisplay.cpp
)
add_library( 
  graphics
  SHARED
  src/Graphics.cpp
)
add_library(
  main_window
  SHARED
  src/MainWindow.cpp
  src/MainWindow.ui
  include/MainWindow.h
)
target_link_libraries(graphics Qt5::Widgets Qt5::Gui Qt5::Core)
target_link_libraries(main_window Qt5::Widgets Qt5::Gui Qt5::Core)
target_link_libraries(video_display Qt5::Widgets Qt5::Gui Qt5::Core)
target_link_libraries(status_display Qt5::Widgets Qt5::Gui Qt5::Core)