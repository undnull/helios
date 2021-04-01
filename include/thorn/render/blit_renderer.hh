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
#include <thorn/fs.hh>
#include <thorn/gl/pipeline.hh>
#include <thorn/gl/texture.hh>
#include <thorn/gl/vertex_array.hh>

namespace thorn::render
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
     * @param source Texture.
     */
    void draw(const gl::Texture2D &source);

private:
    gl::VertexShader vert;
    gl::FragmentShader frag;
    gl::Pipeline pipeline;

    gl::Buffer vbo, ebo;
    gl::VertexArray vao;
};
} // namespace thorn::render
