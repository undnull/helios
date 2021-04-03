/*
 * background_renderer.cc
 * Created: 2021-03-24, 23:14:25.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <thorn/render/background_renderer.hh>
#include <thorn/util/file_io.hh>
#include <iostream>

namespace thorn::render
{
static const vertex vertices[] = {
    { { 0.0f, 0.0f }, { 0.0f, 0.0f } },
    { { 1.0f, 0.0f }, { 1.0f, 0.0f } },
    { { 1.0f, 1.0f }, { 1.0f, 1.0f } },
    { { 0.0f, 1.0f }, { 0.0f, 1.0f } }
};

static constexpr GLsizei NUM_INDICES = 6;

static const GLuint indices[NUM_INDICES] = {
    0, 1, 2,
    0, 2, 3
};

BackgroundRenderer::BackgroundRenderer(bool stretch)
{
    ubo0.storage<gl::BufferUsage::DYNAMIC>(sizeof(ubo0_s));
    ubo1.storage<gl::BufferUsage::DYNAMIC>(sizeof(ubo1_s));

    vbo.storage<gl::BufferUsage::STATIC>(sizeof(vertices));
    vbo.subData(0, vertices, sizeof(vertices));

    ebo.storage<gl::BufferUsage::STATIC>(sizeof(indices));
    ebo.subData(0, indices, sizeof(indices));

    vao.bindVertexBuffer(vbo, 0, offsetof(vertex, position), sizeof(vertex));
    vao.bindVertexBuffer(vbo, 1, offsetof(vertex, texcoord), sizeof(vertex));
    vao.bindElementBuffer(ebo);

    vao.enableAttribute(0);
    vao.enableAttribute(1);

    vao.setAttributeFormat<float>(0, 2, false);
    vao.setAttributeFormat<float>(1, 2, false);

    vao.setAttributeBinding(0, 0);
    vao.setAttributeBinding(1, 1);
}

template<>
bool BackgroundRenderer::loadDefaultShader<gl::ShaderStage::VERTEX>()
{
    const std::vector<uint8_t> binary = util::file_io::read(DEFAULT_VERT);
    if(binary.size() && vert.link(binary)) {
        pipeline.stage(vert);
        return true;
    }

    std::cerr << vert.getInfoLog() << std::endl;
    return false;
}

template<>
bool BackgroundRenderer::loadDefaultShader<gl::ShaderStage::FRAGMENT>()
{
    const std::vector<uint8_t> binary = util::file_io::read(DEFAULT_FRAG);
    if(binary.size() && frag.link(binary)) {
        pipeline.stage(frag);
        return true;
    }

    std::cerr << frag.getInfoLog() << std::endl;
    return false;
}

template<>
bool BackgroundRenderer::loadShader<gl::ShaderStage::VERTEX>(const std::vector<uint8_t> &binary)
{
    if(vert.link(binary)) {
        pipeline.stage(vert);
        return true;
    }

    std::cerr << vert.getInfoLog() << std::endl;
    return false;
}

template<>
bool BackgroundRenderer::loadShader<gl::ShaderStage::FRAGMENT>(const std::vector<uint8_t> &binary)
{
    if(frag.link(binary)) {
        pipeline.stage(frag);
        return true;
    }

    std::cerr << frag.getInfoLog() << std::endl;
    return false;
}

void BackgroundRenderer::setView(math::View &view)
{
    ubo0_s ubo0_i;
    ubo0_i.projection = view.getProjectionMatrix();
    ubo0_i.scale = glm::scale(float4x4_t(1.0f), float3_t(view.getSize(), 0.0f));
    ubo0_i.target_size = view.getSize();
    ubo0_i.view_position = view.getPosition();
    ubo0_i.view_rotation = glm::radians(view.getRotation());
    ubo0_i.view_zoom = view.getZoomFactor();
    ubo0.subData(0, &ubo0_i, sizeof(ubo0_i));
}

void BackgroundRenderer::draw(const gl::Texture2D &texture, const float2_t &texture_size, const float2_t &scroll_factor, bool fit)
{
    ubo1_s ubo1_i;
    ubo1_i.texture_size = texture_size;
    ubo1_i.scroll_factor = scroll_factor;
    ubo1_i.fit = fit ? 1 : 0;
    ubo1.subData(0, &ubo1_i, sizeof(ubo1_i));

    glUseProgram(0);
    glBindProgramPipeline(pipeline.get());
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo0.get());
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubo1.get());
    glBindTextureUnit(0, texture.get());
    glBindVertexArray(vao.get());
    glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, nullptr);
}
} // namespace thorn::render
