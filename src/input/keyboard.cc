/*
 * keyboard.cc
 * Created: 2021-03-10, 15:06:08.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <input/keyboard.hh>

namespace input
{
bool keys_down[GLFW_KEY_LAST + 1] = { 0 };
int pressed_key = GLFW_KEY_UNKNOWN;
int released_key = GLFW_KEY_UNKNOWN;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    bool press = (action == GLFW_PRESS || action == GLFW_REPEAT);
    keys_down[key] = press;
    if(press) {
        pressed_key = key;
        released_key = GLFW_KEY_UNKNOWN;
    }
    else {
        pressed_key = GLFW_KEY_UNKNOWN;
        released_key = key;
    }
}
} // namespace input
