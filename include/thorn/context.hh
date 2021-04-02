/*
 * context.hh
 * Created: 2021-04-01, 22:14:10.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <GLFW/glfw3.h>
#include <iostream>

namespace thorn
{
/**
 * @brief Thorn context.
 * 
 * All the libraries that Thorn is wrapping around
 * should be initialized and terminated here.
 *
 * Use THORN_INIT() in your entry point to create a
 * new context. Do not use the class directly!
 */
class Context {
public:
    /**
     * @brief Constructor.
     * 
     * @note Calls std::terminate() when something is wrong.
     */
    Context();

    /**
     * @brief Destructor.
     * 
     */
    virtual ~Context();

private:
    /**
     * @brief GLFW error handler.
     * 
     * @param code Error code.
     * @param message Error message.
     */
    static void onGlfwError(int code, const char *message);
};

inline Context::Context()
{
    glfwSetErrorCallback(onGlfwError);
    if(!glfwInit())
        std::terminate();
}

inline Context::~Context()
{
    glfwTerminate();
}
} // namespace thorn

/**
 * @brief Creates a new Thorn context.
 * 
 */
#define THORN_INIT()            \
    thorn::Context x_thorn_ctx; \
    static_cast<void>(x_thorn_ctx)
