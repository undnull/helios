/*
 * window.cc
 * Created: 2021-03-30, 20:50:19.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <helios/glfw/window.hh>

namespace hx::glfw
{
void Window::onWindowSize(GLFWwindow *window, int width, int height)
{
    Window *wrapper = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));
    if(wrapper && wrapper->on_resize)
        wrapper->on_resize(width, height);
}
} // namespace hx::glfw
