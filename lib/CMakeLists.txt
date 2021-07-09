add_library(loguru STATIC loguru/loguru.cpp loguru/loguru.hpp)
target_include_directories(loguru PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(gl3w)
add_subdirectory(linear-algebra)