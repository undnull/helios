/*
 * blit_renderer.cc
 * Created: 2021-03-30, 12:18:01.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <thorn/fs.hh>
#include <thorn/render/blit_renderer.hh>
#include <thorn/types.hh>
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

BlitRenderer::BlitRenderer(const fs::path &vs, const fs::path &fs)
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

    const std::vector<uint8_t> vert_spv = fs::readBinaryFile(vs);
    if(!vert.link(vert_spv.data(), vert_spv.size()))
        std::cerr << vert.getInfoLog() << std::endl;

    const std::vector<uint8_t> frag_spv = fs::readBinaryFile(fs);
    if(!frag.link(frag_spv.data(), frag_spv.size()))
        std::cerr << frag.getInfoLog() << std::endl;

    pipeline.stage(vert);
    pipeline.stage(frag);
}

void BlitRenderer::draw(const gl::Texture &source)
{
    glUseProgram(0);
    glBindProgramPipeline(pipeline.get());
    glBindTextureUnit(0, source.get());
    glBindVertexArray(vao.get());
    glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, nullptr);
}
} // namespace thorn::render
