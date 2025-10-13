cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME TARGET_NAME)
file(GLOB SRC CONFIGURE_DEPENDS "*.cc" "*.hh")

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
	qt_add_library(${TARGET_NAME} STATIC ${SRC})
else()
	add_library(${TARGET_NAME} ${SRC})
endif()

target_link_libraries(${TARGET_NAME}
PUBLIC
	Qt${QT_VERSION_MAJOR}::Core
)
target_include_directories(${TARGET_NAME}
PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)
target_compile_options(${TARGET_NAME}
PRIVATE
	$<$<C_COMPILER_ID:MSVC>:/W4>
	$<$<NOT:$<C_COMPILER_ID:MSVC>>:-Wall -Wpedantic>
)
