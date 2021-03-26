/*
 * tilemap_renderer.hh
 * Created: 2021-03-24, 14:48:12.
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

namespace hx::render
{
class TilemapRenderer {
public:
    struct alignas(16) ubo0_s {
        float4x4_t projection;
        float4x4_t scale;
        float4x4_t view;
        float4x4_t transform;
    };

    struct alignas(16) ubo1_s {
        float2_t tileset_size;
        float2_t tilemap_size;
        float tile_size;
    };

public:
    TilemapRenderer(int width, int height);

    void setView(const math::View &view);
    void draw(const math::Transform &transform, const float2_t &size, const float2_t &tileset_size, float tile_size, const gl::Texture &tilemap, const gl::Texture &tileset);

private:
    gl::VertexShader vert;
    gl::FragmentShader frag;
    gl::Pipeline pipeline;

    gl::Buffer vbo, ebo;
    gl::VertexArray vao;

    gl::Buffer ubo0;
    gl::Buffer ubo1;
};
} // namespace hx::render
