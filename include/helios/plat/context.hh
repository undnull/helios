/*
 * context.hh
 * Created: 2021-03-24, 12:11:35.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <GLFW/glfw3.h>
#include <exception>

namespace plat
{
class Context {
public:
    Context();
    virtual ~Context();

private:
    static void onError(int code, const char *message);
};

inline Context::Context()
{
    glfwSetErrorCallback(onError);
    if(!glfwInit())
        std::terminate();
}

inline Context::~Context()
{
    glfwTerminate();
}
} // namespace plat

#define PLAT_CREATE_CONTEXT()     \
    plat::Context x_plat_context; \
    static_cast<void>(x_plat_context)
