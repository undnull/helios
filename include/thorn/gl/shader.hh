/*
 * shader.hh
 * Created: 2021-03-01, 20:47:32.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <glad/gl.h>
#include <string>
#include <utility>
#include <vector>

namespace thorn::gl
{
/**
 * @brief Shader stage.
 * 
 */
enum class ShaderStage {
    VERTEX,
    FRAGMENT
};

template<ShaderStage T>
constexpr GLenum SHADER_STAGE = 0;
template<>
constexpr GLenum SHADER_STAGE<ShaderStage::VERTEX> = GL_VERTEX_SHADER;
template<>
constexpr GLenum SHADER_STAGE<ShaderStage::FRAGMENT> = GL_FRAGMENT_SHADER;

/**
 * @brief GPU-side program.
 * 
 * @tparam T Shader stage.
 */
template<ShaderStage T>
class Shader {
public:
    /**
     * @brief Constructor
     * 
     */
    Shader();

    /**
     * @brief Move constructor.
     * 
     * @param rhs Existing shader.
     */
    Shader(Shader<T> &&rhs);
    Shader(const Shader<T> &rhs) = delete;

    /**
     * @brief Destructor
     * 
     */
    virtual ~Shader();

    /**
     * @brief Assign operator.
     * 
     * @param rhs Existing shader.
     * @return this
     */
    Shader<T> &operator=(Shader<T> &&rhs);
    Shader<T> &operator=(const Shader<T> &rhs) = delete;

    /**
     * @brief Loads a SPIR-V binary, specializes and links the shader.
     * 
     * @param binary SPIR-V binary.
     * @return true if succeeded and false otherwise.
     */
    bool link(const std::vector<uint8_t> &binary);

    /**
     * @brief Gets the shader info log.
     *
     * @return Info log.
     */
    constexpr const std::string &getInfoLog() const;

    /**
     * @brief Gets an OpenGL handle of the shader.
     * 
     * @return An OpenGL handle.
     */
    constexpr GLuint get() const;

private:
    std::string info_log;
    GLuint program;
};

using VertexShader = Shader<ShaderStage::VERTEX>;
using FragmentShader = Shader<ShaderStage::FRAGMENT>;

template<ShaderStage T>
inline Shader<T>::Shader()
    : info_log()
{
    program = glCreateProgram();
    glProgramParameteri(program, GL_PROGRAM_SEPARABLE, GL_TRUE);
}

template<ShaderStage T>
inline Shader<T>::Shader(Shader<T> &&rhs)
    : info_log(rhs.info_log), program(rhs.program)
{
    rhs.info_log.clear();
    rhs.program = 0;
}

template<ShaderStage T>
inline Shader<T>::~Shader()
{
    glDeleteProgram(program);
}

template<ShaderStage T>
inline Shader<T> &Shader<T>::operator=(Shader<T> &&rhs)
{
    Shader copy(std::move(rhs));
    std::swap(copy.info_log, info_log);
    std::swap(copy.program, program);
    return *this;
}

template<ShaderStage T>
inline bool Shader<T>::link(const std::vector<uint8_t> &binary)
{
    GLint status;

    info_log.clear();

    GLuint shader = glCreateShader(SHADER_STAGE<T>);
    glShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, binary.data(), static_cast<GLsizei>(binary.size()));
    glSpecializeShader(shader, "main", 0, nullptr, nullptr);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE) {
        GLint length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        if(length) {
            info_log.resize(static_cast<size_t>(length));
            glGetShaderInfoLog(shader, length, nullptr, info_log.data());
        }

        glDeleteShader(shader);
        return false;
    }

    glAttachShader(program, shader);
    glLinkProgram(program);

    glDeleteShader(shader);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if(status == GL_FALSE) {
        GLint length;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        if(length) {
            info_log.resize(static_cast<size_t>(length));
            glGetShaderInfoLog(shader, length, nullptr, info_log.data());
        }

        return false;
    }

    return true;
}

template<ShaderStage T>
inline constexpr const std::string &Shader<T>::getInfoLog() const
{
    return info_log;
}

template<ShaderStage T>
inline constexpr GLuint Shader<T>::get() const
{
    return program;
}
} // namespace thorn::gl
