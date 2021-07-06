#include <iostream>

#define TEST(function) \
    if (function()) {  \
        success++;               \
        std::cout << "TEST: [" << #function << "] SUCCESS" << std::endl; \
    } else { \
        std::cerr << "TEST: [" << #function << "] FAILED" << std::endl;\
    } \
    total++;

#define TEST_ASSERT(x) if (!(x)) return false
#define TEST_COMPLETE return true

#include <graphics/Window.hpp>

namespace Window {
    bool CreationTest() {
        Graphics::Window win("Test Window");
        TEST_COMPLETE;
    }
}

int main() {
    unsigned int success = 0, total = 0;
    TEST(Window::CreationTest)
}