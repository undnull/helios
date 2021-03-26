/*
 * sprite_renderer.cc
 * Created: 2021-03-08, 19:02:15.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <helios/logger.hh>
#include <helios/fs.hh>
#include <helios/render/sprite_renderer.hh>
#include <algorithm>

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

SpriteRenderer::SpriteRenderer(int width, int height)
{
    Logger logger("SpriteRenderer");

    const float4x4_t projection_m = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

    ubo.storage<gl::BufferUsage::DYNAMIC>(sizeof(ubo_s));
    ubo.subData(offsetof(ubo_s, projection), &projection_m, sizeof(projection_m));

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

    const std::vector<uint8_t> vert_spv = fs::readBinaryFile("assets/shaders/sprite.vert.spv");
    if(!vert.link(vert_spv.data(), vert_spv.size()))
        logger.log(vert.getInfoLog());

    const std::vector<uint8_t> frag_spv = fs::readBinaryFile("assets/shaders/sprite.frag.spv");
    if(!frag.link(frag_spv.data(), frag_spv.size()))
        logger.log(frag.getInfoLog());

    pipeline.stage(vert);
    pipeline.stage(frag);
}

void SpriteRenderer::setView(const math::View &view)
{
    const float4x4_t view_m = view.getMatrix();
    ubo.subData(offsetof(ubo_s, view), &view_m, sizeof(view_m));
}

void SpriteRenderer::draw(const std::vector<math::Transform> &transforms, const gl::Texture &texture, const float2_t &size)
{
    const float4x4_t size_m = glm::scale(float4x4_t(1.0f), float3_t(size, 1.0f));
    ubo.subData(offsetof(ubo_s, scale), &size_m, sizeof(size_m));

    instances.clear();
    std::transform(transforms.cbegin(), transforms.cend(), std::back_inserter(instances), [](const math::Transform &t) {
        return t.getMatrix();
    });

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
} // namespace hx::render
