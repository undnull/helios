/*
 * glad.hh
 * Created: 2021-03-24, 11:47:01.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <vector>

namespace thorn::glad
{
/**
 * @brief Loads the needed GL version and checks
 * for the required extensions.
 *
 * Since the project is using the latest GL features,
 * we would need to check for those features to be present.
 *
 * @note If OpenGL 4.6 is present, returns true regardless of the extensions.
 *
 * @return true if the loading succeeded and false otherwise.
 */
static inline bool load()
{
    if(gladLoadGL(glfwGetProcAddress)) {
        bool ext = true;
        ext = ext && GLAD_GL_ARB_shader_storage_buffer_object;
        ext = ext && GLAD_GL_ARB_separate_shader_objects;
        ext = ext && GLAD_GL_ARB_direct_state_access;
        ext = ext && GLAD_GL_ARB_gl_spirv;
        return GLAD_GL_VERSION_4_6 || ext;
    }
    return false;
}
} // namespace thorn::glad
