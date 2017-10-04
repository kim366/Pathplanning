cmake_minimum_required (VERSION 3.8)
project(pathplanning)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

find_package(SFML 2.4 COMPONENTS system window graphics REQUIRED)

include_directories(include ${SFML_INCLUDE_DIR})
aux_source_directory(src sources)
aux_source_directory(src/Gui sources_gui)
aux_source_directory(tests sources_test)

option(BUILD_TESTS "Build tests. Requires catch single include in include folder" OFF)

add_executable(gui ${sources} ${sources_gui} gui/main.cpp)
set_target_properties(gui PROPERTIES CXX_STANDARD 17)
target_link_libraries(gui ${SFML_LIBRARIES})

if(BUILD_TESTS)
	add_executable(tests ${sources} ${sources_gui} ${sources_test})
	set_target_properties(tests PROPERTIES CXX_STANDARD 17)
	target_link_libraries(tests ${SFML_LIBRARIES})
endif()

add_compile_options(-Wall -Wextra -Wshadow -Werror -Wconversion -Wno-sign-conversion)
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -O0")
