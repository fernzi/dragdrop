cmake_minimum_required(VERSION 3.18..3.23)

project(
	dragdrop
	VERSION 1.1.0
	LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)

add_subdirectory(doc/man)
add_subdirectory(etc/xdg)
add_subdirectory(src)
