/*
 * window.hh
 * Created: 2021-03-24, 10:08:55.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <GLFW/glfw3.h>
#include <utility>

namespace hx::glfw
{
/**
 * @brief A window.
 * 
 */
class Window {
public:
    /**
     * @brief Opens a new window.
     * 
     * @param width Window width in pixels.
     * @param height Window height in pixels.
     * @param title Window title.
     * @param fullscreen Fullscreen.
     * @param border False if window is borderless.
     * @param samples Number of samples (MSAA).
     */
    Window(int width, int height, const char *title, bool fullscreen = false, bool border = true, int samples = 0);
    Window(Window &&rhs) = delete;
    Window(const Window &rhs) = delete;

    /**
     * @brief Closes the window.
     * 
     */
    virtual ~Window();

    Window &operator=(Window &&rhs);
    Window &operator=(const Window &rhs) = delete;

    /**
     * @brief Sets the window title.
     * 
     * @param title Window title.
     */
    void setTitle(const char *title);

    /**
     * @brief Sets the window swap interval.
     * 
     * Swap interval of 0 means that vertical sync is disabled.
     *
     * @param interval Swap interval.
     */
    void setSwapInterval(int interval);

    /**
     * @brief Sets the window close status.
     * 
     * @param close True if window needs to be closed.
     */
    void setShouldClose(bool close);

    /**
     * @brief Returns window close status.
     * 
     * @return true if window is going to close.
     */
    bool shouldClose() const;

    /**
     * @brief Makes the OpenGL context current.
     * 
     */
    void makeContextCurrent();

    /**
     * @brief Swaps the window buffers.
     * 
     */
    void swapBuffers();

    /**
     * @brief Handles events.
     * 
     * @note Calls glfwWaitEventsTimeout() if the window
     * is out of focus therefore saves some CPU time.
     */
    void handleEvents();

    /**
     * @brief Returns a pointer to the actual GLFW window.
     * 
     * @return Window pointer.
     */
    constexpr GLFWwindow *get() const;

private:
    GLFWwindow *window;
};

inline Window::Window(int width, int height, const char *title, bool fullscreen, bool border, int samples)
{
    glfwWindowHint(GLFW_DECORATED, border ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_SAMPLES, samples);
    window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    glfwMakeContextCurrent(window);
}

inline Window::~Window()
{
    glfwDestroyWindow(window);
}

inline void Window::setTitle(const char *title)
{
    glfwSetWindowTitle(window, title);
}

inline void Window::setSwapInterval(int interval)
{
    glfwMakeContextCurrent(window);
    glfwSwapInterval(interval);
}

inline void Window::setShouldClose(bool close)
{
    glfwSetWindowShouldClose(window, close ? GLFW_TRUE : GLFW_FALSE);
}

inline bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window) == GLFW_TRUE;
}

inline void Window::makeContextCurrent()
{
    glfwMakeContextCurrent(window);
}

inline void Window::swapBuffers()
{
    glfwSwapBuffers(window);
}

inline void Window::handleEvents()
{
    if(glfwGetWindowAttrib(window, GLFW_FOCUSED))
        glfwPollEvents();
    else
        glfwWaitEventsTimeout(0.05);
}

inline constexpr GLFWwindow *Window::get() const
{
    return window;
}
} // namespace hx::glfw
