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
/**
 * @brief Scrolling background renderer.
 * 
 */
class BackgroundRenderer {
public:
    /**
     * @brief Uniform Buffer structure.
     * 
     */
    struct alignas(16) ubo0_s {
        float4x4_t projection;
        float4x4_t scale;
        float2_t target_size;
        float2_t view_position;
        float view_rotation;
        float view_zoom;
    };

    
    /**
     * @brief Uniform Buffer structure.
     * 
     */
    struct alignas(16) ubo1_s {
        float2_t texture_size;
        float2_t scroll_factor;
        GLuint fit;
    };

    static constexpr const char *DEFAULT_VERT = "assets/shaders/background.vert.spv";
    static constexpr const char *DEFAULT_FRAG = "assets/shaders/background.frag.spv";

public:
    /**
     * @brief Constructor
     * 
     * @param vs Vertex shader file path.
     * @param fs Fragment shader file path.
     */
    BackgroundRenderer(bool stretch = true, const fs::path &vs = DEFAULT_VERT, const fs::path &fs = DEFAULT_FRAG);

    /**
     * @brief Sets the view.
     * 
     * @param view View.
     */
    void setView(math::View &view);

    /**
     * @brief Draws a background layer.
     * 
     * @param texture Background texture.
     * @param texture_size Background texture's size.
     * @param scroll_factor Scrolling factor (pseudo-distance).
     * @param fit Fit to the screen height.
     */
    void draw(const gl::Texture &texture, const float2_t &texture_size, const float2_t &scroll_factor, bool fit);

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
