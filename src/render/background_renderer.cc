/*
 * background_renderer.cc
 * Created: 2021-03-24, 23:14:25.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <thorn/fs.hh>
#include <thorn/render/background_renderer.hh>
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

BackgroundRenderer::BackgroundRenderer(bool stretch, const fs::path &vs, const fs::path &fs)
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

    const std::vector<uint8_t> vert_spv = fs::readBinaryFile(vs);
    if(!vert.link(vert_spv.data(), vert_spv.size()))
        std::cerr << vert.getInfoLog() << std::endl;

    const std::vector<uint8_t> frag_spv = fs::readBinaryFile(fs);
    if(!frag.link(frag_spv.data(), frag_spv.size()))
        std::cerr << frag.getInfoLog() << std::endl;

    pipeline.stage(vert);
    pipeline.stage(frag);
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
