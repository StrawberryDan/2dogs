cmake_minimum_required(VERSION 3.20)
project(graphics VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)

enable_testing()

add_subdirectory(gl3w)
add_library(loguru STATIC loguru/loguru.cpp loguru/loguru.hpp)
add_subdirectory(linear-algebra)
add_subdirectory(graphics)