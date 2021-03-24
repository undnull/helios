/*
 * tilemap_renderer.cc
 * Created: 2021-03-24, 15:14:30.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <helios/logger.hh>
#include <helios/plat/fs.hh>
#include <helios/render/tilemap_renderer.hh>

namespace render
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

TilemapRenderer::TilemapRenderer(int width, int height)
{
    Logger logger("tilemap_renderer");

    const float4x4_t projection_m = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f, -1.0f, 1.0f);

    ubo0.storage<gl::BufferUsage::DYNAMIC>(sizeof(ubo0_s));
    ubo0.subData(offsetof(ubo0_s, projection), &projection_m, sizeof(projection_m));

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

    const std::vector<uint8_t> vert_spv = plat::fs::readBinaryFile("assets/shaders/tilemap.vert.spv");
    if(!vert.link(vert_spv.data(), vert_spv.size()))
        logger.log("sprite.vert: %s", vert.getInfoLog());

    const std::vector<uint8_t> frag_spv = plat::fs::readBinaryFile("assets/shaders/tilemap.frag.spv");
    if(!frag.link(frag_spv.data(), frag_spv.size()))
        logger.log("sprite.frag: %s", frag.getInfoLog());

    pipeline.stage(vert);
    pipeline.stage(frag);
}

void TilemapRenderer::setView(const math::View &view)
{
    const float4x4_t view_m = view.getMatrix();
    ubo0.subData(offsetof(ubo0_s, view), &view_m, sizeof(view_m));
}

void TilemapRenderer::draw(const math::Transform &transform, const float2_t &size, const float2_t &tileset_size, float tile_size, const gl::Texture &tilemap, const gl::Texture &tileset)
{
    // The tilemap mesh is internally set to be a unit one ([0.0, 0.0] to [1.0, 1.0])
    // thus the additional scale matrix will just resize it to the target size
    const float4x4_t size_m = glm::scale(float4x4_t(1.0f), float3_t(size, 1.0f));
    ubo0.subData(offsetof(ubo0_s, scale), &size_m, sizeof(size_m));

    const float4x4_t transform_m = transform.getMatrix();
    ubo0.subData(offsetof(ubo0_s, transform), &transform_m, sizeof(transform_m));

    ubo1_s ubo1_i;
    ubo1_i.tileset_size = tileset_size;
    ubo1_i.tilemap_size = size;
    ubo1_i.tile_size = tile_size;
    ubo1.subData(0, &ubo1_i, sizeof(ubo1_i));

    glUseProgram(0);
    glBindProgramPipeline(pipeline.get());
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo0.get());
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubo1.get());
    glBindTextureUnit(0, tileset.get());
    glBindTextureUnit(1, tilemap.get());
    glBindVertexArray(vao.get());
    glDrawElements(GL_TRIANGLES, NUM_INDICES, GL_UNSIGNED_INT, nullptr);
}
} // namespace render
