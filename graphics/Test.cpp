#include <catch2/catch_all.hpp>

#include <GL/gl3w.h>
#include <loguru.h>
#include <graphics/Window.hpp>
#include <graphics/Image.hpp>
#include <graphics/Texture.hpp>
#include <filesystem>
#include <iostream>

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

TEST_CASE("Image Loading") {
	std::cout << std::filesystem::current_path() << std::endl;
	Graphics::Image img("testdata/test.png");
	REQUIRE(img.get_width() == 738);
	REQUIRE(img.get_height() == 669);
}

TEST_CASE("Texture Loading") {
	Graphics::Window win;
	win.MakeCurrent();
	Graphics::Image img("testdata/test.png");
	Graphics::Texture tex(img);
	tex.bind();
	REQUIRE(glGetError() == GL_NO_ERROR);
}

int main(int argc, const char **argv) {
    auto session = Catch::Session();
    session.run(argc, argv);
}
