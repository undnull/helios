/*
 * vertex_array.hh
 * Created: 2021-03-01, 21:13:22.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <thorn/gl/buffer.hh>

namespace thorn::gl
{
template<typename T>
constexpr unsigned int ATTRIBUTE_FORMAT = 0;
template<>
constexpr unsigned int ATTRIBUTE_FORMAT<float> = GL_FLOAT;

/**
 * @brief Combination of vertex and element buffers.
 * 
 */
class VertexArray {
public:
    /**
     * @brief Constructor
     * 
     */
    VertexArray();

    /**
     * @brief Move constructor.
     * 
     * @param rhs Existing vertex array.
     */
    VertexArray(VertexArray &&rhs);
    VertexArray(const VertexArray &rhs) = delete;

    /**
     * @brief Destructor
     * 
     */
    virtual ~VertexArray();

    /**
     * @brief Assign operator.
     * 
     * @param rhs Existing vertex array.
     * @return this
     */
    VertexArray &operator=(VertexArray &&rhs);
    VertexArray &operator=(const VertexArray &rhs) = delete;

    /**
     * @brief Binds an element buffer.
     * 
     * @param ebo Element buffer.
     */
    void bindElementBuffer(const Buffer &ebo);

    /**
     * @brief Binds a vertex buffer.
     * 
     * @param vbo Vertex buffer.
     * @param binding Binding index.
     * @param offset Buffer offset in bytes.
     * @param stride Size of a single element in the buffer.
     */
    void bindVertexBuffer(const Buffer &vbo, unsigned int binding, size_t offset, size_t stride);

    /**
     * @brief Enables a vertex attribute.
     * 
     * @param attrib Attribute index.
     */
    void enableAttribute(unsigned int attrib);

    /**
     * @brief Sets the format of a vertex attribute.
     * 
     * @tparam T Attribute type.
     * @param attrib Attribute index.
     * @param count Number of T elements.
     * @param normalized Should these elements be normalized?
     */
    template<typename T>
    void setAttributeFormat(unsigned int attrib, size_t count, bool normalized);

    /**
     * @brief Binds a vertex attribute to a bound vertex buffer.
     * 
     * @param attrib Attribute index.
     * @param binding Vertex buffer binding index.
     */
    void setAttributeBinding(unsigned int attrib, unsigned int binding);

    /**
     * @brief Gets an OpenGL handle of the vertex array.
     * 
     * @return An OpenGL handle.
     */
    constexpr unsigned int get() const;

private:
    unsigned int vaobj;
};

inline VertexArray::VertexArray()
{
    glCreateVertexArrays(1, &vaobj);
}

inline VertexArray::VertexArray(VertexArray &&rhs)
    : vaobj(rhs.vaobj)
{
    rhs.vaobj = 0;
}

inline VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &vaobj);
}

inline VertexArray &VertexArray::operator=(VertexArray &&rhs)
{
    VertexArray copy(std::move(rhs));
    std::swap(copy.vaobj, vaobj);
    return *this;
}

inline void VertexArray::bindElementBuffer(const Buffer &ebo)
{
    glVertexArrayElementBuffer(vaobj, ebo.get());
}

inline void VertexArray::bindVertexBuffer(const Buffer &vbo, unsigned int binding, size_t offset, size_t stride)
{
    glVertexArrayVertexBuffer(vaobj, binding, vbo.get(), static_cast<GLintptr>(offset), static_cast<GLsizei>(stride));
}

inline void VertexArray::enableAttribute(unsigned int attrib)
{
    glEnableVertexArrayAttrib(vaobj, attrib);
}

template<typename T>
inline void VertexArray::setAttributeFormat(unsigned int attrib, size_t count, bool normalized)
{
    glVertexArrayAttribFormat(vaobj, attrib, static_cast<GLint>(count), ATTRIBUTE_FORMAT<T>, normalized ? GL_TRUE : GL_FALSE, 0);
}

inline void VertexArray::setAttributeBinding(unsigned int attrib, unsigned int binding)
{
    glVertexArrayAttribBinding(vaobj, attrib, binding);
}

inline constexpr unsigned int VertexArray::get() const
{
    return vaobj;
}
} // namespace thorn::gl
