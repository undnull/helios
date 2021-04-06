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
#include <thorn/image.hh>
#include <thorn/types.hh>
#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include <utility>

namespace thorn::glfw
{
/**
 * @brief GLFWwindow wrapper.
 * 
 */
class Window {
public:
    template<typename T>
    using handler_list = std::vector<std::function<T>>;

public:
    /**
     * @brief Constructor
     * 
     * @param width Width in pixels.
     * @param height Height in pixels.
     * @param title Window title.
     * @param fullscreen
     */
    Window(int width, int height, const std::string &title, bool fullscreen = false);
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
     * @brief Sets the window size.
     * 
     * @param width Width in pixels.
     * @param height Height in pixels.
     */
    void setSize(int width, int height);

    /**
     * @brief Sets the window title.
     * 
     * @param title Window title.
     */
    void setTitle(const char *title);

    /**
     * @brief Sets the window icon.
     * 
     * @note The const correctness is broken because GLFWimage said so.
     *
     * @param image Icon image.
     */
    void setIcon(Image &image);

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
     * @brief Sets the cursor mode
     * 
     * @param mode GLFW cursor mode.
     */
    void setCursorMode(int mode);

    /**
     * @brief Gets the window close flag value.
     * 
     * @return true if the window needs to be closed.
     */
    bool shouldClose() const;

    /**
     * @brief Gets the window width.
     * 
     * @return Window width in pixels.
     */
    int getWidth() const;

    /**
     * @brief Gets the window height.
     * 
     * @return Window height in pixels.
     */
    int getHeight() const;

    /**
     * @brief Gets the window size.
     * 
     * @param width Width in pixels.
     * @param height Height in pixels.
     */
    void getSize(int &width, int &height) const;

    /**
     * @brief Gets the cursor position.
     * 
     * @return Cursor position.
     */
    const float2_t getCursorPosition() const;

    /**
     * @brief Godot-ish way of processing the keyboard input.
     * 
     * @param key GLFW key.
     * @return true if the key is pressed.
     */
    bool isKeyPressed(int key) const;

    /**
     * @brief Keyboard-ish way of processing the mouse input.
     * 
     * @param key GLFW mouse button.
     * @return true if the button  is pressed.
     */
    bool isMouseButtonPressed(int button) const;

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
    static void onClose(GLFWwindow *window);
    static void onCursorPos(GLFWwindow *window, double x, double y);
    static void onScroll(GLFWwindow *window, double dx, double dy);
    static void onWindowSize(GLFWwindow *window, int width, int height);
    static void onKey(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void onMouseButton(GLFWwindow *window, int button, int action, int mods);
    static void onChar(GLFWwindow *window, unsigned int unicode);

public:
    std::function<void()> on_close;
    std::function<void(float, float)> on_cursor_pos;
    std::function<void(float, float)> on_scroll;
    std::function<void(int, int)> on_window_size;
    std::function<void(int, int, int)> on_key;
    std::function<void(int, int, int)> on_mouse_button;
    std::function<void(unsigned int)> on_char;

private:
    GLFWwindow *window;
};

inline Window::Window(int width, int height, const std::string &title, bool fullscreen)
{
    window = glfwCreateWindow(width, height, title.c_str(), fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetWindowCloseCallback(window, onClose);
    glfwSetCursorPosCallback(window, onCursorPos);
    glfwSetScrollCallback(window, onScroll);
    glfwSetWindowSizeCallback(window, onWindowSize);
    glfwSetKeyCallback(window, onKey);
    glfwSetMouseButtonCallback(window, onMouseButton);
    glfwSetCharCallback(window, onChar);
    glfwMakeContextCurrent(window);
}

inline Window::~Window()
{
    glfwDestroyWindow(window);
}

inline void Window::setSize(int width, int height)
{
    glfwSetWindowSize(window, width, height);
}

inline void Window::setTitle(const char *title)
{
    glfwSetWindowTitle(window, title);
}

inline void Window::setIcon(Image &image)
{
    GLFWimage icon;
    icon.pixels = reinterpret_cast<unsigned char *>(image.getPixels());
    image.getSize(icon.width, icon.height);
    glfwSetWindowIcon(window, 1, &icon);
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

inline void Window::setCursorMode(int mode)
{
    glfwSetInputMode(window, GLFW_CURSOR, mode);
}

inline bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window) == GLFW_TRUE;
}

inline int Window::getWidth() const
{
    int width;
    glfwGetWindowSize(window, &width, nullptr);
    return width;
}

inline int Window::getHeight() const
{
    int height;
    glfwGetWindowSize(window, nullptr, &height);
    return height;
}

inline void Window::getSize(int &width, int &height) const
{
    glfwGetWindowSize(window, &width, &height);
}

inline const float2_t Window::getCursorPosition() const
{
    double x, y;
    glfwGetCursorPos(window, &x, &y);
    return float2_t(x, y);
}

inline bool Window::isKeyPressed(int key) const
{
    return glfwGetKey(window, key) == GLFW_PRESS;
}

inline bool Window::isMouseButtonPressed(int button) const
{
    return glfwGetMouseButton(window, button) == GLFW_PRESS;
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
} // namespace thorn::glfw
