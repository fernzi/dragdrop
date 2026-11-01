cmake_minimum_required(VERSION 3.19..4.3)

project(dragdrop
  VERSION 1.2.0
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.4 REQUIRED
  COMPONENTS
    Core
    Network
    Widgets
)
qt_standard_project_setup()

add_subdirectory(doc/man)
add_subdirectory(etc/xdg)
add_subdirectory(src)
