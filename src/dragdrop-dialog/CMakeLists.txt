cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME BIN_NAME)
file(GLOB SRC CONFIGURE_DEPENDS "*.cc" "*.hh" "*.ui")

qt_add_executable(${BIN_NAME} ${SRC})

target_link_libraries(${BIN_NAME}
  PRIVATE
    Qt::Widgets
)
target_compile_definitions(${BIN_NAME}
PRIVATE
	DRAGDROP_NAME="${BIN_NAME}"
	DRAGDROP_VERSION="${PROJECT_VERSION}"
)
target_compile_options(${BIN_NAME}
PRIVATE
	$<$<C_COMPILER_ID:MSVC>:/W3>
	$<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall>
)

install(TARGETS ${BIN_NAME}
	DESTINATION ${CMAKE_INSTALL_LIBEXECDIR}
)
