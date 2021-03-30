/*
 * blit_renderer.hh
 * Created: 2021-03-30, 12:42:43.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <helios/gl/pipeline.hh>
#include <helios/gl/texture.hh>
#include <helios/gl/vertex_array.hh>
#include <helios/fs.hh>

namespace hx::render
{
/**
 * @brief Textured quad renderer.
 * 
 */
class BlitRenderer {
public:
    static constexpr const char *DEFAULT_VERT = "assets/shaders/blit.vert.spv";
    static constexpr const char *DEFAULT_FRAG = "assets/shaders/blit.frag.spv";

public:
    /**
     * @brief Constructor.
     * 
     * @param vs Vertex shader file path.
     * @param fs Fragment shader file path.
     */
    BlitRenderer(const fs::path &vs = DEFAULT_VERT, const fs::path &fs = DEFAULT_FRAG);

    /**
     * @brief Draws a full-frame textued quad.
     * 
     * @param texture Texture.
     */
    void draw(const gl::Texture &texture);

private:
    gl::VertexShader vert;
    gl::FragmentShader frag;
    gl::Pipeline pipeline;

    gl::Buffer vbo, ebo;
    gl::VertexArray vao;
};
} // namespace hx::render
