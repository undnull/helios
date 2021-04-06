/*
 * sprite_renderer.cc
 * Created: 2021-03-08, 19:02:15.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <thorn/render/sprite_renderer.hh>
#include <thorn/util/file_io.hh>
#include <algorithm>
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

SpriteRenderer::SpriteRenderer()
{
    ubo.storage<gl::BufferUsage::DYNAMIC>(sizeof(ubo_s));

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
bool SpriteRenderer::loadDefaultShader<gl::ShaderStage::VERTEX>()
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
bool SpriteRenderer::loadDefaultShader<gl::ShaderStage::FRAGMENT>()
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
bool SpriteRenderer::loadShader<gl::ShaderStage::VERTEX>(const std::vector<uint8_t> &binary)
{
    if(vert.link(binary)) {
        pipeline.stage(vert);
        return true;
    }

    std::cerr << vert.getInfoLog() << std::endl;
    return false;
}

template<>
bool SpriteRenderer::loadShader<gl::ShaderStage::FRAGMENT>(const std::vector<uint8_t> &binary)
{
    if(frag.link(binary)) {
        pipeline.stage(frag);
        return true;
    }

    std::cerr << frag.getInfoLog() << std::endl;
    return false;
}

void SpriteRenderer::setView(math::View &view)
{
    ubo_s ubo_i;
    ubo_i.projection = view.getProjectionMatrix();
    ubo_i.view = view.getViewMatrix();
    ubo.subData(0, &ubo_i, sizeof(ubo_i));
}

void SpriteRenderer::draw(const std::vector<float4x4_t> &instances, const gl::Texture2D &texture, const float2_t &size)
{
    const float4x4_t size_m = glm::scale(float4x4_t(1.0f), float3_t(size, 1.0f));
    ubo.subData(offsetof(ubo_s, scale), &size_m, sizeof(size_m));

    const size_t num_instances = instances.size();
    const size_t ssbo_size = sizeof(float4x4_t) * num_instances;

    ssbo.storage<gl::BufferUsage::DYNAMIC>(ssbo_size);
    ssbo.subData(0, instances.data(), ssbo_size);

    glUseProgram(0);
    glBindProgramPipeline(pipeline.get());
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo.get());
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, ssbo.get());
    glBindTextureUnit(0, texture.get());
    glBindVertexArray(vao.get());
    glDrawElementsInstanced(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, nullptr, static_cast<GLsizei>(num_instances));
}
} // namespace thorn::render
