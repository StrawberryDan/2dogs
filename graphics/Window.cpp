#include "Window.hpp"

#include <GLFW/glfw3.h>
#include <loguru/loguru.hpp>

static std::atomic_uint         INSTANCE_COUNT(0);
static std::atomic<GLFWwindow*> CURRENT_CONTEXT(nullptr);

#define GLFW_INIT \
    if (INSTANCE_COUNT == 0) if (glfwInit() != GLFW_TRUE) { \
        LOG_F(FATAL, "Unable to load GLFW3!");                \
    }

#define GLFW_TERMINATE \
    if (INSTANCE_COUNT == 0) glfwTerminate();

namespace Graphics {
    Window::Window(): title("No Title") {
        GLFW_INIT;
        context = glfwCreateWindow(800, 600, title.c_str(), nullptr, nullptr);
        INSTANCE_COUNT++;
    }

    Window::Window(std::string title): title(title) {
        GLFW_INIT;
        context = glfwCreateWindow(800, 600, title.c_str(), nullptr, nullptr);
        INSTANCE_COUNT++;
    }

    Window::Window(unsigned int width, unsigned int height, std::string title): title(title) {
        GLFW_INIT;
        context = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
        INSTANCE_COUNT++;
    }

    Window::Window(const Window &other) {
        title = other.title;
        auto size = other.GetSize();
        context = glfwCreateWindow(size[0], size[1], title.c_str(), nullptr, nullptr);
        INSTANCE_COUNT++;
    }

    Window &Window::operator=(const Window &other) {
        if (context) { glfwDestroyWindow(context); INSTANCE_COUNT--; }
        title = other.title;
        auto size = other.GetSize();
        context = glfwCreateWindow(size[0], size[1], title.c_str(), nullptr, nullptr);
        INSTANCE_COUNT++;
        return *this;
    }

    Window::Window(Window &&other) {
        // Swap out contexts
        // (Other should not be glfwDestroyWindow'd since it is nullptr)
        context = other.context;
        other.context = nullptr;
        title = other.title;
        other.title = std::string();
    }

    Window &Window::operator=(Window &&other) {
        // Swap contexts so old one will be deleted.
        if (context) { glfwDestroyWindow(context); INSTANCE_COUNT--; }
        context = other.context;
        other.context = nullptr;
        title = other.title;
        other.title = std::string();
        return *this;
    }

    Window::~Window() {
        if (CURRENT_CONTEXT == context) CURRENT_CONTEXT = nullptr;
        if (context) glfwDestroyWindow(context);
        INSTANCE_COUNT--;
        GLFW_TERMINATE;
    }

    void Window::MakeCurrent() {
        if (context) { glfwMakeContextCurrent(context); CURRENT_CONTEXT = context; }
    }

    bool Window::IsCurrent() const {
        return (context != nullptr && CURRENT_CONTEXT == context);
    }

    Vec2i Window::GetSize() const {
        if (context) {
            Vec2i size;
            glfwGetWindowSize(context, &size[0], &size[1]);
            return size;
        } else {
            return Vec2i();
        }
    }

    void Window::SetSize(Vec2i size) {
        glfwSetWindowSize(context, size[0], size[1]);
    }

    std::string Window::GetTitle() const {
        return title;
    }

    void Window::SetTitle(std::string title) {
        this->title = title;
        glfwSetWindowTitle(context, title.c_str());
    }
}