cmake_minimum_required(VERSION 3.18..3.23)

project(
	dragdrop
	VERSION 1.1.0
	LANGUAGES CXX
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(
	QT
	NAMES Qt6 Qt5
	COMPONENTS Widgets
	REQUIRED
)
find_package(
	Qt${QT_VERSION_MAJOR}
	COMPONENTS Widgets
	REQUIRED
)

include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED)

set(PROJECT_SOURCES
	src/dragdrop-application.cc
	src/dragdrop-application.hh
	src/dragdrop-dragarea.cc
	src/dragdrop-dragarea.hh
	src/dragdrop-droparea.cc
	src/dragdrop-droparea.hh
	src/dragdrop-window.cc
	src/dragdrop-window.hh
	src/dragdrop.cc
)

add_executable(
	${PROJECT_NAME}
	${PROJECT_SOURCES}
)
target_compile_features(
	${PROJECT_NAME} PRIVATE
	cxx_std_11
)
set_target_properties(
	${PROJECT_NAME} PROPERTIES
	CXX_EXTENSIONS OFF
)
if(IPO_SUPPORTED)
	set_target_properties(
		${PROJECT_NAME} PROPERTIES
		INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
	)
endif()
target_compile_definitions(
	${PROJECT_NAME} PRIVATE
	DRAGDROP_NAME="${PROJECT_NAME}"
	DRAGDROP_VERSION="${PROJECT_VERSION}"
)
target_link_libraries(
	${PROJECT_NAME} PRIVATE
	Qt${QT_VERSION_MAJOR}::Widgets
)

include(GNUInstallDirs)
install(
	TARGETS ${PROJECT_NAME}
	RUNTIME
	DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
install(
	FILES ${CMAKE_SOURCE_DIR}/etc/xdg/dragdrop.desktop
	DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
)
install(
	FILES ${CMAKE_SOURCE_DIR}/etc/xdg/dragdrop.svg
	DESTINATION ${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/apps
)

add_subdirectory(doc/man)
