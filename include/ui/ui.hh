/*
 * ui.hh
 * Created: 2021-03-07, 12:31:49.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <util/command_line.hh>
#include <util/imgui.hh>

struct GLFWwindow;

namespace ui
{
void init(GLFWwindow *window);
const ImGuiIO &beginFrame();
void endFrame();
} // namespace ui
