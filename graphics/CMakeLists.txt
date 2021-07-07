configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.template ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_custom_target(
    graphics-docs
    COMMAND doxygen
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

find_package(glfw3 REQUIRED)

add_library(graphics STATIC
    Window.hpp
    Window.cpp
)

target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(graphics PUBLIC glfw linear-algebra loguru)

add_executable(graphics-test Test.cpp)
target_link_libraries(graphics-test PRIVATE graphics)

add_test(NAME graphics-test COMMAND graphics-test)