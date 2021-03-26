/*
 * background_renderer.hh
 * Created: 2021-03-24, 23:07:36.
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
#include <helios/math/view.hh>
#include <helios/fs.hh>

namespace hx::render
{
class BackgroundRenderer {
public:
    struct ubo_s {
        float4x4_t projection;
        float4x4_t scale;
        float2_t target_size;
        float2_t texture_size;
        float2_t scroll_factor;
        float2_t view_position;
        float view_rotation;
        float view_zoom;
    };

    const fs::path DEFAULT_VERT = "assets/shaders/background.vert.spv";
    const fs::path DEFAULT_FRAG = "assets/shaders/background.frag.spv";

public:
    BackgroundRenderer(int width, int height, const fs::path &vs, const fs::path &fs);
    BackgroundRenderer(int width, int height);

    void setView(const math::View &view);
    void draw(const gl::Texture &texture, const float2_t &texture_size, const float2_t &scroll_factor);

private:
    gl::VertexShader vert;
    gl::FragmentShader frag;
    gl::Pipeline pipeline;

    gl::Buffer vbo, ebo;
    gl::VertexArray vao;

    gl::Buffer ubo;
};

inline BackgroundRenderer::BackgroundRenderer(int width, int height)
    : BackgroundRenderer(width, height, DEFAULT_VERT, DEFAULT_FRAG)
{

}
} // namespace hx::render
