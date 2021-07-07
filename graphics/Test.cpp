#include <iostream>

#include <GL/gl3w.h>
#include <loguru.h>

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
        win.MakeCurrent();
        while (!win.ShouldClose()) { 
            win.PollEvents();
            glClear(GL_COLOR_BUFFER_BIT);
            win.SwapBuffers();
        }
        TEST_COMPLETE;
    }

    bool MultipleWindows() {
        Graphics::Window win1("Test Window 1");
        Graphics::Window win2("Test Window 2");
        Graphics::Window win3("Test Window 3");

        while (!(win1.ShouldClose() && win2.ShouldClose() && win3.ShouldClose())) {
            win1.MakeCurrent();
            glClearColor(1.0, 0.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            win2.MakeCurrent();
            glClearColor(0.0, 1.0, 0.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            win3.MakeCurrent();
            glClearColor(0.0, 0.0, 1.0, 1.0);
            glClear(GL_COLOR_BUFFER_BIT);
            win1.PollEvents();
            win2.PollEvents();
            win3.PollEvents();
            win1.SwapBuffers();
            win2.SwapBuffers();
            win3.SwapBuffers();
        }
        TEST_COMPLETE;
    }
}

int main() {
    unsigned int success = 0, total = 0;
    TEST(Window::CreationTest)
    TEST(Window::MultipleWindows)

    return (success == total) ? 0 : -1;
}