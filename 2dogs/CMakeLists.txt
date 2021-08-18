configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_custom_target(
    2dogs-docs
    COMMAND doxygen
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

find_package(glfw3 REQUIRED)

add_library(2dogs STATIC
    Window.hpp
    Window.cpp
)

target_include_directories(2dogs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(2dogs PUBLIC gl3w glfw linear-algebra loguru)

add_executable(2dogs-test Test.cpp)
target_link_libraries(2dogs-test PRIVATE 2dogs Catch2::Catch2)
add_test(NAME 2dogs-test COMMAND 2dogs-test)
