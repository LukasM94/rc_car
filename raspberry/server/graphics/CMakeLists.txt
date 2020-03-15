
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library( 
  graphics
  SHARED
  src/Graphics.cpp
)
target_link_libraries(graphics Qt5::Widgets)
