cmake_minimum_required(VERSION 3.18..3.23)

project(
	dragdrop
	VERSION 0.1.0
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

find_program(SCDOC scdoc)
if(SCDOC)
	set(MAN_TGT ${PROJECT_NAME}.1)
	add_custom_command(
		COMMAND ${SCDOC} < ${CMAKE_SOURCE_DIR}/doc/man/${MAN_TGT}.scd > ${MAN_TGT}
		COMMENT "Building manpage ${MAN_TGT}"
		MAIN_DEPENDENCY doc/man/${MAN_TGT}.scd
		OUTPUT ${MAN_TGT}
		VERBATIM
	)
	add_custom_target(
		man ALL
		DEPENDS ${MAN_TGT}
	)
endif()

include(CheckIPOSupported)
check_ipo_supported(RESULT IPO_SUPPORTED)

file(GLOB PROJECT_SOURCES CONFIGURE_DEPENDS "src/*.cc" "src/*.hh")

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
if(MAN_TGT)
	install(
		FILES ${CMAKE_BINARY_DIR}/${MAN_TGT}
		DESTINATION "${CMAKE_INSTALL_MANDIR}/man1"
	)
endif()
