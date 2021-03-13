/*
 * logger_out.hh
 * Created: 2021-03-06, 22:53:45.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <util/imgui.hh>

namespace ui
{
class LoggerOut {
public:
    void draw(const ImGuiIO &io);
};
} // namespace ui
