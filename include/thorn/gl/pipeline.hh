/*
 * pipeline.hh
 * Created: 2021-03-01, 20:54:37.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <thorn/gl/shader.hh>

namespace thorn::gl
{
template<ShaderStage T>
constexpr GLenum SHADER_STAGE_BIT = 0;
template<>
constexpr GLenum SHADER_STAGE_BIT<ShaderStage::VERTEX> = GL_VERTEX_SHADER_BIT;
template<>
constexpr GLenum SHADER_STAGE_BIT<ShaderStage::FRAGMENT> = GL_FRAGMENT_SHADER_BIT;

/**
 * @brief Combination of different shader stages.
 * 
 */
class Pipeline {
public:
    /**
     * @brief Constructor
     * 
     */
    Pipeline();

    /**
     * @brief Move constructor.
     * 
     * @param rhs Existing pipeline.
     */
    Pipeline(Pipeline &&rhs);
    Pipeline(const Pipeline &rhs) = delete;

    /**
     * @brief Destructor
     * 
     */
    virtual ~Pipeline();

    /**
     * @brief Assign operator.
     * 
     * @param rhs Existing pipeline.
     * @return this
     */
    Pipeline &operator=(Pipeline &&rhs);
    Pipeline &operator=(const Pipeline &rhs) = delete;

    /**
     * @brief Attaches a new shader stage to the pipeline.
     * 
     * @tparam T Shader stage.
     * @param shader Shader.
     */
    template<ShaderStage T>
    void stage(const Shader<T> &shader);

    /**
     * @brief Gets an OpenGL handle of the pipeline.
     * 
     * @return An OpenGL handle.
     */
    constexpr GLuint get() const;

private:
    GLuint pipeline;
};

inline Pipeline::Pipeline()
{
    glCreateProgramPipelines(1, &pipeline);
}

inline Pipeline::Pipeline(Pipeline &&rhs)
    : pipeline(rhs.pipeline)
{
    rhs.pipeline = 0;
}

inline Pipeline::~Pipeline()
{
    glDeleteProgramPipelines(1, &pipeline);
}

inline Pipeline &Pipeline::operator=(Pipeline &&rhs)
{
    Pipeline copy(std::move(rhs));
    std::swap(copy.pipeline, pipeline);
    return *this;
}

template<ShaderStage T>
inline void Pipeline::stage(const Shader<T> &shader)
{
    glUseProgramStages(pipeline, SHADER_STAGE_BIT<T>, shader.get());
}

inline constexpr GLuint Pipeline::get() const
{
    return pipeline;
}
} // namespace thorn::gl
