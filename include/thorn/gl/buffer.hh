/*
 * buffer.hh
 * Created: 2021-03-01, 20:44:30.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <glad/gl.h>
#include <utility>

namespace thorn::gl
{
/**
 * @brief Buffer usage hint.
 * 
 */
enum class BufferUsage {
    STATIC,
    STREAM,
    DYNAMIC,
};

template<BufferUsage T>
constexpr GLenum BUFFER_USAGE = 0;
template<>
constexpr GLenum BUFFER_USAGE<BufferUsage::STATIC> = GL_STATIC_DRAW;
template<>
constexpr GLenum BUFFER_USAGE<BufferUsage::STREAM> = GL_STREAM_DRAW;
template<>
constexpr GLenum BUFFER_USAGE<BufferUsage::DYNAMIC> = GL_DYNAMIC_DRAW;

/**
 * @brief General-purpose chunk of GPU-side memory.
 * 
 */
class Buffer {
public:
    /**
     * @brief Constructor.
     * 
     */
    Buffer();

    /**
     * @brief Move constructor.
     * 
     * @param rhs Existing buffer.
     */
    Buffer(Buffer &&rhs);
    Buffer(const Buffer &&rhs) = delete;

    /**
     * @brief Destructor.
     * 
     */
    virtual ~Buffer();

    /**
     * @brief Assign operator.
     * 
     * @param rhs Existing buffer.
     * @return this
     */
    Buffer &operator=(Buffer &&rhs);
    Buffer &operator=(const Buffer &rhs) = delete;

    /**
     * @brief Initializes the buffer's GPU-side storage.
     * 
     * @tparam T Buffer usage.
     * @param size New size in bytes.
     */
    template<BufferUsage T>
    void storage(size_t size);

    /**
     * @brief Writes a chunk of data to the GPU-side storage.
     * 
     * @param offset Write offset in bytes.
     * @param data Data to write.
     * @param size Data size in bytes.
     */
    void subData(size_t offset, const void *data, size_t size);

    /**
     * @brief Gets an OpenGL handle of the buffer.
     * 
     * @return An OpenGL handle.
     */
    constexpr GLuint get() const;

private:
    GLuint buffer;
};

inline Buffer::Buffer()
{
    glCreateBuffers(1, &buffer);
}

inline Buffer::Buffer(Buffer &&rhs)
{
    buffer = rhs.buffer;
    rhs.buffer = 0;
}

inline Buffer::~Buffer()
{
    glDeleteBuffers(1, &buffer);
}

inline Buffer &Buffer::operator=(Buffer &&rhs)
{
    Buffer copy(std::move(rhs));
    std::swap(copy.buffer, buffer);
    return *this;
}

template<BufferUsage T>
inline void Buffer::storage(size_t size)
{
    glNamedBufferData(buffer, static_cast<GLsizeiptr>(size), nullptr, BUFFER_USAGE<T>);
}

inline void Buffer::subData(size_t offset, const void *data, size_t size)
{
    glNamedBufferSubData(buffer, static_cast<GLintptr>(offset), static_cast<GLsizeiptr>(size), data);
}

inline constexpr GLuint Buffer::get() const
{
    return buffer;
}
} // namespace thorn::gl
