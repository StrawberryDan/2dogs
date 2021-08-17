configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

add_custom_target(
    graphics-docs
    COMMAND doxygen
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

find_package(glfw3 REQUIRED)

add_library(graphics STATIC
    Window.hpp
    Window.cpp
    Image.hpp
    Image.cpp
    Texture.hpp
    Texture.cpp
)

target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(graphics PUBLIC gl3w glfw linear-algebra loguru stb)
add_dependencies(graphics graphics-docs)

add_executable(graphics-test Test.cpp)
target_link_libraries(graphics-test PRIVATE graphics Catch2::Catch2)
add_test(NAME graphics-test COMMAND graphics-test)
