#include "Window.hpp"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <loguru/loguru.hpp>

static std::atomic_bool         GL_FUNCTIONS_LOADED(false);
static std::atomic_uint         INSTANCE_COUNT(0);
static std::atomic<GLFWwindow*> CURRENT_CONTEXT(nullptr);

#define GLFW_INIT \
    if (INSTANCE_COUNT == 0) if (glfwInit() != GLFW_TRUE) { \
        LOG_F(FATAL, "Unable to load GLFW3!");              \
    }                                                       \
                                                            \
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);          \
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);          

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
        std::shared_lock lk(other.mutex);
        title = other.title;
        auto size = other.GetSize();
        context = glfwCreateWindow(size[0], size[1], title.c_str(), nullptr, nullptr);
        INSTANCE_COUNT++;
    }

    Window &Window::operator=(const Window &other) {
        std::unique_lock lk1(mutex);
        std::shared_lock lk2(other.mutex);
        if (context) { glfwDestroyWindow(context); INSTANCE_COUNT--; }
        title = other.title;
        auto size = other.GetSize();
        context = glfwCreateWindow(size[0], size[1], title.c_str(), nullptr, nullptr);
        INSTANCE_COUNT++;
        return *this;
    }

    Window::Window(Window &&other) {
        std::shared_lock lk(other.mutex);
        // Swap out contexts
        // (Other should not be glfwDestroyWindow'd since it is nullptr)
        context = other.context;
        other.context = nullptr;
        title = other.title;
        other.title = std::string();
    }

    Window &Window::operator=(Window &&other) {
        std::unique_lock lk1(mutex);
        std::shared_lock lk2(other.mutex);
        // Swap contexts so old one will be deleted.
        if (context) { glfwDestroyWindow(context); INSTANCE_COUNT--; }
        context = other.context;
        other.context = nullptr;
        title = other.title;
        other.title = std::string();
        return *this;
    }

    Window::~Window() {
        std::unique_lock lk(mutex);
        if (CURRENT_CONTEXT == context) CURRENT_CONTEXT = nullptr;
        if (context) glfwDestroyWindow(context);
        INSTANCE_COUNT--;
        GLFW_TERMINATE;
    }

    void Window::MakeCurrent() {
        std::unique_lock lk(mutex);
        if (context) { glfwMakeContextCurrent(context); CURRENT_CONTEXT = context; }
        if (!GL_FUNCTIONS_LOADED) { 
            gl3wInit();
            GL_FUNCTIONS_LOADED = true;
        }
    }

    bool Window::IsCurrent() const {
        std::shared_lock lk(mutex);
        return (context != nullptr && CURRENT_CONTEXT == context);
    }

    Vec2i Window::GetSize() const {
        std::shared_lock lk(mutex);
        if (context) {
            Vec2i size;
            glfwGetWindowSize(context, &size[0], &size[1]);
            return size;
        } else {
            return Vec2i();
        }
    }

    void Window::SetSize(Vec2i size) {
        std::unique_lock lk(mutex);
        glfwSetWindowSize(context, size[0], size[1]);
    }

    std::string Window::GetTitle() const {
        std::shared_lock lk(mutex);
        return title;
    }

    void Window::SetTitle(std::string title) {
        std::unique_lock lk(mutex);
        this->title = title;
        glfwSetWindowTitle(context, title.c_str());
    }

    void Window::SwapBuffers() {
        std::unique_lock lk(mutex);
        glfwSwapBuffers(context);
    }

    void Window::PollEvents() {
        glfwPollEvents();
    }

    bool Window::ShouldClose() const {
        return glfwWindowShouldClose(context);
    }
}