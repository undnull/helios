/*
 * window.cc
 * Created: 2021-03-30, 20:50:19.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <thorn/glfw/window.hh>

namespace thorn::glfw
{
void Window::onClose(GLFWwindow *window)
{
    Window *wrapper = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if(wrapper && wrapper->on_close)
        wrapper->on_close();
}

void Window::onMousePosition(GLFWwindow *window, double x, double y)
{
    Window *wrapper = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if(wrapper && wrapper->on_mouse_position)
        wrapper->on_mouse_position(static_cast<float>(x), static_cast<float>(y));
}

void Window::onScroll(GLFWwindow *window, double dx, double dy)
{
    Window *wrapper = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if(wrapper && wrapper->on_scroll)
        wrapper->on_scroll(static_cast<float>(dx), static_cast<float>(dy));
}

void Window::onWindowSize(GLFWwindow *window, int width, int height)
{
    Window *wrapper = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if(wrapper && wrapper->on_window_size)
        wrapper->on_window_size(width, height);
}

void Window::onKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    Window *wrapper = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if(wrapper) {
        if(action == GLFW_PRESS)
            wrapper->last_pressed_key = key;
        else if(action == GLFW_RELEASE)
            wrapper->last_released_key = key;
        if(wrapper->on_key)
            wrapper->on_key(key, action, mods);
    }
}

void Window::onMouseButton(GLFWwindow *window, int button, int action, int mods)
{
    Window *wrapper = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if(wrapper) {
        if(action == GLFW_PRESS)
            wrapper->last_pressed_mb = button;
        else if(action == GLFW_RELEASE)
            wrapper->last_released_mb = button;
        if(wrapper->on_mouse_button)
            wrapper->on_mouse_button(button, action, mods);
    }
}

void Window::onChar(GLFWwindow *window, unsigned int unicode)
{
    Window *wrapper = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if(wrapper && wrapper->on_char)
        wrapper->on_char(unicode);
}
} // namespace thorn::glfw
