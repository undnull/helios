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
 * @brief Window wrapper.
 * 
 */
class Window {
public:
    /**
     * @brief Constructor
     * 
     * @param width Width in pixels.
     * @param height Height in pixels.
     * @param title Window title.
     * @param fullscreen 
     * @param border False if borderless.
     * @param samples Number of samples (MSAA).
     */
    Window(int width, int height, const char *title, bool fullscreen = false, bool border = true, int samples = 0);
    Window(Window &&rhs) = delete;
    Window(const Window &rhs) = delete;

    /**
     * @brief Destructor.
     * 
     * Closes the window.
     */
    virtual ~Window();

    Window &operator=(Window &&rhs) = delete;
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
     * @note Swap interval of 0 means that vertical
     * synchronization is disabled.
     * 
     * @param interval Swap interval.
     */
    void setSwapInterval(int interval);

    /**
     * @brief Sets the window close flag.
     * 
     * @param close True if window needs to be closed.
     */
    void setShouldClose(bool close);

    /**
     * @brief Gets the window close flag value.
     * 
     * @return true if the window needs to be closed.
     */
    bool shouldClose() const;

    /**
     * @brief Makes the GL context current.
     * 
     */
    void makeContextCurrent();

    /**
     * @brief Swaps the window buffers.
     * 
     */
    void swapBuffers();

    /**
     * @brief Polls and calls GLFW events.
     * 
     * @note If the window is out of focus, glfwWaitEventsInterval
     * will be used saving some CPU time.
     */
    void handleEvents();

    /**
     * @brief Returns the GLFW window.
     * 
     * @return GLFW window.
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
