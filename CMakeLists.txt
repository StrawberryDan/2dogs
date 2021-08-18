cmake_minimum_required(VERSION 3.20)
project(graphics VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

enable_testing()
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/lib/Catch2/extras)
include(CTest)
include(Catch)

add_custom_target(COMPILE_COMMANDS ALL COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}/compile_commands.json)
add_subdirectory(lib)
add_subdirectory(graphics)
