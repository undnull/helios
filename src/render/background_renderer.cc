/*
 * background_renderer.cc
 * Created: 2021-03-24, 23:14:25.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <helios/logger.hh>
#include <helios/fs.hh>
#include <helios/render/background_renderer.hh>

namespace hx::render
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

BackgroundRenderer::BackgroundRenderer(int width, int height)
{
    Logger logger("BackgroundRenderer");

    const float2_t target_size = float2_t(width, height);
    const float4x4_t projection = glm::ortho(0.0f, target_size.x, target_size.y, 0.0f, -1.0f, 1.0f);
    const float4x4_t scale = glm::scale(float4x4_t(1.0f), float3_t(target_size, 1.0f));

    ubo.storage<gl::BufferUsage::DYNAMIC>(sizeof(ubo_s));
    ubo.subData(offsetof(ubo_s, projection), &projection, sizeof(projection));
    ubo.subData(offsetof(ubo_s, scale), &scale, sizeof(scale));
    ubo.subData(offsetof(ubo_s, target_size), &target_size, sizeof(target_size));

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

    const std::vector<uint8_t> vert_spv = fs::readBinaryFile("assets/shaders/background.vert.spv");
    if(!vert.link(vert_spv.data(), vert_spv.size()))
        logger.log(vert.getInfoLog());

    const std::vector<uint8_t> frag_spv = fs::readBinaryFile("assets/shaders/background.frag.spv");
    if(!frag.link(frag_spv.data(), frag_spv.size()))
        logger.log(frag.getInfoLog());

    pipeline.stage(vert);
    pipeline.stage(frag);
}

void BackgroundRenderer::setView(const math::View &view)
{
    const float2_t view_position = view.getPosition();
    const float view_rotation = glm::radians(view.getRotation());
    const float view_zoom = view.getZoomFactor();

    ubo.subData(offsetof(ubo_s, view_position), &view_position, sizeof(view_position));
    ubo.subData(offsetof(ubo_s, view_rotation), &view_rotation, sizeof(view_rotation));
    ubo.subData(offsetof(ubo_s, view_zoom), &view_zoom, sizeof(view_zoom));
}

void BackgroundRenderer::draw(const gl::Texture &texture, const float2_t &texture_size, const float2_t &scroll_factor)
{
    ubo.subData(offsetof(ubo_s, texture_size), &texture_size, sizeof(texture_size));
    ubo.subData(offsetof(ubo_s, scroll_factor), &scroll_factor, sizeof(scroll_factor));

    glUseProgram(0);
    glBindProgramPipeline(pipeline.get());
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo.get());
    glBindTextureUnit(0, texture.get());
    glBindVertexArray(vao.get());
    glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, nullptr);
}
} // namespace hx::render
