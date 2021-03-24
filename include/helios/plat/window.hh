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

namespace plat
{
class Window {
public:
    Window(int width, int height, const char *title, bool fullscreen = false, bool border = true, int samples = 0);
    Window(Window &&rhs);
    Window(const Window &rhs) = delete;

    virtual ~Window();

    Window &operator=(Window &&rhs);
    Window &operator=(const Window &rhs) = delete;

    void setTitle(const char *title);
    void setSwapInterval(int interval);
    void setShouldClose(bool close);

    bool shouldClose() const;

    void makeContextCurrent();

    void swapBuffers();
    void handleEvents();

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

inline Window::Window(Window &&rhs)
{
    window = rhs.window;
    rhs.window = nullptr;
}

inline Window::~Window()
{
    glfwDestroyWindow(window);
}

inline Window &Window::operator=(Window &&rhs)
{
    Window copy(std::move(rhs));
    std::swap(copy.window, window);
    return *this;
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
} // namespace plat
