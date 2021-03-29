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

namespace hx::glfw
{
/**
 * @brief A wrapper class for GLFW init and shutdown functions.
 * 
 */
class Context {
public:
    /**
     * @brief Constructor.
     * 
     * Calls glfwInit().
     * 
     * @note If glfwInit() failed, std::terminate() is called.
     */
    Context();

    /**
     * @brief Destructor.
     * 
     * Calls glfwShutdown().
     */
    virtual ~Context();

private:
    /**
     * @brief Error handler.
     * 
     * @param code Error code.
     * @param message Error message.
     */
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
} // namespace hx::glfw

#define HX_CREATE_GLFW_CONTEXT()        \
    hx::glfw::Context x_glfw_context;   \
    static_cast<void>(x_glfw_context)
