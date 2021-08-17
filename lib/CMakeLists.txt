add_library(loguru STATIC loguru/loguru.cpp loguru/loguru.hpp)
target_include_directories(loguru PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(stb INTERFACE)
target_include_directories(stb INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(stb INTERFACE STB_IMAGE_IMPLEMENTATION)

add_subdirectory(gl3w)
add_subdirectory(linear-algebra)
add_subdirectory(Catch2)
