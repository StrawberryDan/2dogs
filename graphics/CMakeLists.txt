find_package(glfw3 REQUIRED)

add_library(graphics STATIC
    Window.hpp
    Window.cpp
)
target_include_directories(graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(graphics PUBLIC glfw linear-algebra)

add_executable(graphics-test Test.cpp)
target_link_libraries(graphics-test PRIVATE graphics)

add_test(NAME graphics-test COMMAND graphics-test)