cmake_minimum_required(VERSION 3.18..3.23)

project(
	dragdrop
	VERSION 1.1.0
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED
	COMPONENTS Widgets
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED
	COMPONENTS Widgets
)

include(GNUInstallDirs)

add_subdirectory(doc/man)
add_subdirectory(etc/xdg)
add_subdirectory(src)
