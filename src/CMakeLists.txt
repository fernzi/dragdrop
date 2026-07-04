set(TARGET_NAME ${CMAKE_PROJECT_NAME})

set(PROGRAM_NAME ${CMAKE_PROJECT_NAME})
set(PROGRAM_VERSION ${CMAKE_PROJECT_VERSION})
configure_file(config.hh.in config.hh @ONLY)

file(GLOB SRC CONFIGURE_DEPENDS "*.cc" "*.hh" "*.ui")

qt_add_executable(${TARGET_NAME}
  WIN32 MACOSX_BUNDLE
  ${SRC}
)
target_link_libraries(${TARGET_NAME}
  PRIVATE
    Qt::Core
    Qt::Network
    Qt::Widgets
)
target_include_directories(${TARGET_NAME}
  PUBLIC
    ${CMAKE_CURRENT_BINARY_DIR}
)
target_compile_options(${TARGET_NAME}
  PRIVATE
    $<$<C_COMPILER_ID:MSVC>:/W4>
    $<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wpedantic>
)

install(TARGETS ${TARGET_NAME})
