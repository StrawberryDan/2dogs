#include <catch2/catch_all.hpp>

#include <GL/gl3w.h>
#include <loguru.h>
#include <graphics/Window.hpp>

TEST_CASE("Create Window") {
    Graphics::Window win;
    win.MakeCurrent();
    while (!win.ShouldClose()) { 
        win.PollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        win.SwapBuffers();
    }
}

TEST_CASE("Multiple Windows") {
    Graphics::Window win1;
    Graphics::Window win2;
    Graphics::Window win3;

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
}


int main(int argc, const char **argv) {
    auto session = Catch::Session();
    session.run(argc, argv);
}