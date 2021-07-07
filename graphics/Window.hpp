#pragma once

#include <string>
#include <atomic>
#include <shared_mutex>
#include <linear-algebra/Vector.hpp>

using namespace LinearAlgebra;

struct GLFWwindow;

namespace Graphics {
    /**
     * Platform independant window and OpenGL context.
     */
    class Window {
    private:
        /// Mutex to access
        mutable std::shared_mutex mutex;
        /// Display title of the window
        std::string title;
        /// Internal handle to the window
        GLFWwindow *context;
    public:
        /// Creates the window with default values
        Window();
        /// Creates the window with a specified title and default size.
        Window(std::string title);
        /// Creates the window with specified size and title
        Window(unsigned int width, unsigned int height, std::string title);
        /// Copys another window creating a new identical one
        Window(const Window&);
        /// Copies another window and terminates current one
        Window &operator=(const Window&);
        /// Moves a window
        Window(Window &&);
        /// Moves a window and terminates the current one
        Window &operator=(Window &&);
        /// Terminates the current window
        ~Window();

        /// Makes this window the context for all following OpenGL functions until the next call to this method.
        void MakeCurrent();
        /// Returns whether this window is the current OpenGL context.
        bool IsCurrent() const;

        /// Returns the size of this window.
        Vec2i GetSize() const;
        /// Sets the size of this window to the specified value.
        void SetSize(Vec2i size);

        /// Returns the title of this window.
        std::string GetTitle() const;
        /// Sets the display title of the window to the specified value.
        void SetTitle(std::string title);

        /// Swap the graphics buffer for this window
        void SwapBuffers();

        /// Poll the operating system for new events across all windows.
        static void PollEvents();

        /// Controls whether the operating system requests the window to close.
        bool ShouldClose() const;
    };
}