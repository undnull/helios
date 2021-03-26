/*
 * loader.hh
 * Created: 2021-03-24, 11:47:01.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <glad/glad.h>
#include <vector>

namespace hx::gl
{
bool load()
{
    if(gladLoadGL()) {
        bool ext = true;
        ext = ext && GLAD_GL_ARB_shader_storage_buffer_object;
        ext = ext && GLAD_GL_ARB_separate_shader_objects;
        ext = ext && GLAD_GL_ARB_direct_state_access;
        ext = ext && GLAD_GL_ARB_gl_spirv;
        return GLAD_GL_VERSION_4_6 || ext;
    }
    return false;
}
} // namespace hx::gl
