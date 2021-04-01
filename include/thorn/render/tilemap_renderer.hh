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
#include <thorn/fs.hh>
#include <thorn/gl/pipeline.hh>
#include <thorn/gl/texture.hh>
#include <thorn/gl/vertex_array.hh>
#include <thorn/math/transform.hh>
#include <thorn/math/view.hh>

namespace thorn::render
{
/**
 * @brief Tilemap renderer.
 * 
 */
class TilemapRenderer {
public:
    /**
     * @brief Uniform Buffer structure
     * 
     */
    struct alignas(16) ubo0_s {
        float4x4_t projection;
        float4x4_t scale;
        float4x4_t view;
        float4x4_t transform;
    };

    /**
     * @brief Uniform Buffer structure
     * 
     */
    struct alignas(16) ubo1_s {
        float2_t tileset_size;
        float2_t tilemap_size;
        float tile_size;
    };

    static constexpr const char *DEFAULT_VERT = "assets/shaders/tilemap.vert.spv";
    static constexpr const char *DEFAULT_FRAG = "assets/shaders/tilemap.frag.spv";

public:
    /**
     * @brief Constructor.
     * 
     * @param vs Vertex shader file path.
     * @param fs Fragment shader file path.
     */
    TilemapRenderer(const fs::path &vs = DEFAULT_VERT, const fs::path &fs = DEFAULT_FRAG);

    /**
     * @brief Sets the view parameters.
     * 
     * @param view View.
     */
    void setView(math::View &view);

    /**
     * @brief Draws a tilemap.
     * 
     * @param transform Tilemap transform.
     * @param size Tilemap size in pixels.
     * @param tileset_size Tileset size in pixels.
     * @param tile_size Tile size in pixels.
     * @param tilemap Tilemap texture (acts as a lookup table).
     * @param tileset Tileset texture.
     */
    void draw(math::Transform &transform, const float2_t &size, const float2_t &tileset_size, float tile_size, const gl::Texture2D &tilemap, const gl::Texture2D &tileset);

private:
    gl::VertexShader vert;
    gl::FragmentShader frag;
    gl::Pipeline pipeline;

    gl::Buffer vbo, ebo;
    gl::VertexArray vao;

    gl::Buffer ubo0;
    gl::Buffer ubo1;
};
} // namespace thorn::render
