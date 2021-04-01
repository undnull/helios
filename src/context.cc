/*
 * context.cc
 * Created: 2021-03-24, 12:13:35.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <thorn/context.hh>
#include <iostream>

namespace thorn
{
void Context::onGlfwError(int code, const char *message)
{
    std::cerr << "GLFW error " << code << ": " << message << std::endl;
}
} // namespace thorn
