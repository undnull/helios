/*
 * blit_renderer.cc
 * Created: 2021-03-30, 12:18:01.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <thorn/render/blit_renderer.hh>
#include <thorn/types.hh>
#include <thorn/util/file_io.hh>
#include <iostream>

namespace thorn::render
{
static const vertex vertices[] = {
    { { -1.0f, -1.0f }, { 0.0f, 0.0f } },
    { { +1.0f, -1.0f }, { 1.0f, 0.0f } },
    { { +1.0f, +1.0f }, { 1.0f, 1.0f } },
    { { -1.0f, +1.0f }, { 0.0f, 1.0f } }
};

static constexpr GLsizei NUM_INDICES = 6;

static const GLuint indices[NUM_INDICES] = {
    0, 1, 2,
    0, 2, 3
};

BlitRenderer::BlitRenderer()
{
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
bool BlitRenderer::loadDefaultShader<gl::ShaderStage::VERTEX>()
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
bool BlitRenderer::loadDefaultShader<gl::ShaderStage::FRAGMENT>()
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
bool BlitRenderer::loadShader<gl::ShaderStage::VERTEX>(const std::vector<uint8_t> &binary)
{
    if(vert.link(binary)) {
        pipeline.stage(vert);
        return true;
    }

    std::cerr << vert.getInfoLog() << std::endl;
    return false;
}

template<>
bool BlitRenderer::loadShader<gl::ShaderStage::FRAGMENT>(const std::vector<uint8_t> &binary)
{
    if(frag.link(binary)) {
        pipeline.stage(frag);
        return true;
    }

    std::cerr << frag.getInfoLog() << std::endl;
    return false;
}

void BlitRenderer::draw(const gl::Texture2D &source)
{
    glUseProgram(0);
    glBindProgramPipeline(pipeline.get());
    glBindTextureUnit(0, source.get());
    glBindVertexArray(vao.get());
    glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, nullptr);
}
} // namespace thorn::render
