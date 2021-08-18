cmake_minimum_required(VERSION 3.20)
project(2dogs VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

if (CMAKE_EXPORT_COMPILE_COMMANDS)
	add_custom_target(COMPILE_COMMANDS ALL COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json)
endif()

add_subdirectory(third_party)
add_subdirectory(2dogs)
