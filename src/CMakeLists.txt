set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(
	QT NAMES Qt5 Qt6
	REQUIRED
	COMPONENTS Widgets
)
find_package(
	Qt${QT_VERSION_MAJOR} REQUIRED
	COMPONENTS Widgets
)

include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED)

set(BIN_NAME ${PROJECT_NAME} CACHE STRING "Executable name")

set(PROJECT_SOURCES
	application.cc
	application.hh
	dragarea.cc
	dragarea.hh
	droparea.cc
	droparea.hh
	main.cc
	window.cc
	window.hh
)

add_executable(${BIN_NAME} ${PROJECT_SOURCES})
target_link_libraries(
	${BIN_NAME} PRIVATE
	Qt${QT_VERSION_MAJOR}::Widgets
)
target_compile_definitions(
	${BIN_NAME} PRIVATE
	DRAGDROP_NAME="${BIN_NAME}"
	DRAGDROP_VERSION="${PROJECT_VERSION}"
)
target_compile_options(
	${BIN_NAME} PRIVATE
	$<$<C_COMPILER_ID:MSVC>:/W3>
	$<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall>
)
set_target_properties(
	${BIN_NAME} PROPERTIES
	$<$<IPO_SUPPORTED>:INTERPROCEDURAL_OPTIMIZATION_RELEASE ON>
)

install(
	TARGETS ${BIN_NAME}
	RUNTIME
	DESTINATION "${CMAKE_INSTALL_BINDIR}"
)
