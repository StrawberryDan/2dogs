#include "Window.hpp"

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <loguru/loguru.hpp>
#include <map>

static std::atomic_bool         GL_FUNCTIONS_LOADED(false);
static std::atomic_uint         INSTANCE_COUNT(0);
static std::atomic<Graphics::Window*> CURRENT_CONTEXT(nullptr);
static std::map<GLFWwindow*, Graphics::Window*> REGISTERED_WINDOWS;

#define GLFW_INIT \
    if (INSTANCE_COUNT == 0) if (glfwInit() != GLFW_TRUE) { \
        LOG_F(FATAL, "Unable to load GLFW3!");              \
    }                                                       
        

#define GLFW_TERMINATE \
    if (INSTANCE_COUNT == 0) glfwTerminate();

namespace Graphics {
    Window::Settings::Settings() :
        size{800, 600},
        title("Window"),
        fullscreen(false),
        resizable(false),
        terminate_on_close(true),
        lock_aspect_ratio(true)
        {}

    Window::Window(): settings() {
        GLFW_INIT;
        Create();
        INSTANCE_COUNT++;
    }

    Window::Window(Window::Settings settings): settings(settings) {
        GLFW_INIT;
        Create();
        INSTANCE_COUNT++;
    }

    Window::Window(const Window &other): settings(other.settings) {
        std::shared_lock lk(other.mutex);
        Create();
        INSTANCE_COUNT++;
    }

    Window &Window::operator=(const Window &other) {
        std::unique_lock lk1(mutex);
        std::shared_lock lk2(other.mutex);
        if (context) glfwDestroyWindow(context);
        settings = other.settings;
        Create();
        return *this;
    }

    Window::Window(Window &&other): settings(other.settings) {
        std::shared_lock lk(other.mutex);
        // Swap out contexts
        // (Other should not be glfwDestroyWindow'd since it is nullptr)
        other.settings = Settings();
        context = other.context;
        other.context = nullptr;
    }

    Window &Window::operator=(Window &&other) {
        std::unique_lock lk1(mutex);
        std::shared_lock lk2(other.mutex);
        // Swap contexts so old one will be deleted.
        if (context) { glfwDestroyWindow(context); INSTANCE_COUNT--; }
        context = other.context;
        other.context = nullptr;
        settings = other.settings;
        other.settings = Settings();
        return *this;
    }

    Window::~Window() {
        std::unique_lock lk1(mutex);
        std::unique_lock lk2(context_mutex);
        Terminate();
        INSTANCE_COUNT--;
        GLFW_TERMINATE;
    }

    void Window::Terminate() {
        REGISTERED_WINDOWS.erase(context);
        if (CURRENT_CONTEXT == this) CURRENT_CONTEXT = nullptr;
        if (context) glfwDestroyWindow(context);
        context = nullptr;
    }

    void Window::MakeCurrent() {
        std::unique_lock lk(context_mutex);
        if (context) { glfwMakeContextCurrent(context); CURRENT_CONTEXT = this; }
        if (!GL_FUNCTIONS_LOADED) { 
            gl3wInit();
            GL_FUNCTIONS_LOADED = true;
        }
    }

    bool Window::IsCurrentContext() const {
        return (context != nullptr && CURRENT_CONTEXT == this);
    }

    std::unique_lock<std::mutex> Window::LockContext() {
        if (!IsCurrentContext()) MakeCurrent();
        return std::move( std::unique_lock(context_mutex) );
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
        if (context) glfwSetWindowSize(context, size[0], size[1]);
    }

    std::string Window::GetTitle() const {
        std::shared_lock lk(mutex);
        return settings.title;
    }

    void Window::SetTitle(std::string title) {
        std::unique_lock lk(mutex);
        settings.title = title;
        if (context) glfwSetWindowTitle(context, title.c_str());
    }

    void Window::SwapBuffers() {
        std::unique_lock lk(mutex);
        if (context) glfwSwapBuffers(context);
    }

    void Window::PollEvents() {
        glfwPollEvents();
    }

    bool Window::ShouldClose() const {
        if (context) return glfwWindowShouldClose(context);
        return true;
    }

    void Window::Create() {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);          
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);  
        glfwWindowHint(GLFW_RESIZABLE, settings.resizable ? GLFW_TRUE : GLFW_FALSE);
    
        context = glfwCreateWindow(
            settings.size[0], settings.size[1],
            settings.title.c_str(),
            settings.fullscreen ? glfwGetPrimaryMonitor() : nullptr,
            nullptr);

        REGISTERED_WINDOWS[context] = this;

        glfwSetWindowAspectRatio(context, settings.size[0], settings.size[1]);

        if (settings.terminate_on_close) {
            glfwSetWindowCloseCallback(context, Window::DefaultCloseCallback);
        }
    }

    void Window::DefaultCloseCallback(GLFWwindow *window) {
        REGISTERED_WINDOWS[window]->Terminate();
    }
}