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

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(${BIN_NAME}
		MANUAL_FINALIZATION
		${PROJECT_SOURCES}
	)
else()
	add_executable(${BIN_NAME}
		${PROJECT_SOURCES}
	)
endif()

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

install(TARGETS ${BIN_NAME})

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(qt-cmake-test)
endif()
