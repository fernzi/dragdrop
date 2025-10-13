cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME BIN_NAME)
file(GLOB SRC CONFIGURE_DEPENDS "*.cc" "*.hh" "*.ui")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_executable(${BIN_NAME} MANUAL_FINALIZATION ${SRC})
else()
	add_executable(${BIN_NAME} ${SRC})
endif()

target_link_libraries(${BIN_NAME}
PRIVATE
	Qt${QT_VERSION_MAJOR}::Core
	common
)
target_compile_definitions(${BIN_NAME}
PRIVATE
	LIBEXEC_DIR="${CMAKE_INSTALL_LIBEXECDIR}"
	PROGRAM_NAME="${BIN_NAME}"
	PROGRAM_VERSION="${PROJECT_VERSION}"
)
target_compile_options(${BIN_NAME}
PRIVATE
	$<$<C_COMPILER_ID:MSVC>:/W3>
	$<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall>
)

install(TARGETS ${BIN_NAME})

if(QT_VERSION_MAJOR EQUAL 6)
	qt_finalize_executable(${BIN_NAME})
endif()
