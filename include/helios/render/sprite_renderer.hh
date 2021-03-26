/*
 * sprite_renderer.hh
 * Created: 2021-03-08, 18:48:54.
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
#include <helios/math/transform.hh>
#include <helios/math/view.hh>
#include <vector>

namespace hx::render
{
class SpriteRenderer {
public:
    struct alignas(16) ubo_s {
        float4x4_t projection;
        float4x4_t scale;
        float4x4_t view;
    };

public:
    SpriteRenderer(int width, int height);

    void setView(const math::View &view);
    void draw(const std::vector<math::Transform> &transforms, const gl::Texture &texture, const float2_t &size);

private:
    gl::VertexShader vert;
    gl::FragmentShader frag;
    gl::Pipeline pipeline;

    gl::Buffer vbo, ebo;
    gl::VertexArray vao;

    gl::Buffer ubo;
    gl::Buffer ssbo;

    std::vector<float4x4_t> instances;
};
} // namespace hx::render
