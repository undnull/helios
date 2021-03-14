/*
 * keyboard.hh
 * Created: 2021-03-10, 14:50:21.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <GLFW/glfw3.h>

namespace input
{
extern bool keys_down[];
extern int pressed_key, released_key;

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

inline bool isKeyPressed(int key)
{
    return keys_down[key];
}

inline bool isKeyJustPressed(int key)
{
    return pressed_key == key;
}

inline bool isKeyJustReleased(int key)
{
    return released_key == key;
}
} // namespace input
