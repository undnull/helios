/*
 * texture.hh
 * Created: 2021-03-02, 09:37:49.
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
enum class TextureTarget {
    TEXTURE_2D,
    TEXTURE_2D_ARRAY,
};

template<TextureTarget T>
constexpr GLuint TEXTURE_TARGET = 0;
template<>
constexpr GLuint TEXTURE_TARGET<TextureTarget::TEXTURE_2D> = GL_TEXTURE_2D;
template<>
constexpr GLuint TEXTURE_TARGET<TextureTarget::TEXTURE_2D_ARRAY> = GL_TEXTURE_2D_ARRAY;

/**
 * @brief Chunk of GPU memory to store image data.
 * 
 */
template<TextureTarget T>
class Texture {
public:
    /**
     * @brief Constructor
     * 
     */
    Texture();

    /**
     * @brief Move constructor.
     * 
     * @param rhs Existing texture.
     */
    Texture(Texture<T> &&rhs);
    Texture(const Texture<T> &rhs) = delete;

    /**
     * @brief Destructor
     * 
     */
    virtual ~Texture();

    /**
     * @brief Assign operator.
     * 
     * @param rhs Existing texture.
     * @return this
     */
    Texture<T> &operator=(Texture<T> &&rhs);
    Texture<T> &operator=(const Texture<T> &rhs) = delete;

    /**
     * @brief Initializes the texture's GPU-side storage.
     * 
     * @note This should be called once, otherwise an OpenGL error will be generated.
     *
     * @param width Texture width in pixels.
     * @param height Texture height in pixels.
     * @param format Internal storage format.
     */
    void storage(int width, int height, GLenum format);

    /**
     * @brief Writes a chunk of data to the GPU-side texture storage.
     * 
     * @param width Data's width in pixels.
     * @param height Data's height in pixels.
     * @param format Data's format (eg. GL_RGBA).
     * @param type Data's type (per-pixel, eg. GL_UNSIGNED_BYTE).
     * @param pixels Data pointer.
     */
    void subImage(int width, int height, GLenum format, GLenum type, const void *pixels);

    /**
     * @brief Sets a texture parameter.
     * 
     * @param pname Parameter's name.
     * @param value Parameter's value.
     */
    void setParameter(GLenum pname, int value);

    /**
     * @brief Sets a texture parameter.
     * 
     * @param pname Parameter's name.
     * @param value Parameter's value.
     */
    void setParameter(GLenum pname, float value);

    /**
     * @brief Generates a mipmap.
     * 
     * @note I honestly don't know why would it
     * be used for a 2D applcation...
     */
    void generateMipmap();

    /**
     * @brief Gets an OpenGL handle of the texture.
     * 
     * @return An OpenGL handle.
     */
    constexpr GLuint get() const;

private:
    GLuint texture;
};

using Texture2D = Texture<TextureTarget::TEXTURE_2D>;
using Texture2DArray = Texture<TextureTarget::TEXTURE_2D_ARRAY>;

template<TextureTarget T>
inline Texture<T>::Texture()
{
    glCreateTextures(TEXTURE_TARGET<T>, 1, &texture);
}

template<TextureTarget T>
inline Texture<T>::Texture(Texture &&rhs)
{
    texture = rhs.texture;
    rhs.texture = 0;
}

template<TextureTarget T>
inline Texture<T>::~Texture()
{
    glDeleteTextures(1, &texture);
}

template<TextureTarget T>
inline Texture<T> &Texture<T>::operator=(Texture<T> &&rhs)
{
    Texture copy(std::move(rhs));
    std::swap(copy.texture, texture);
    return *this;
}

template<TextureTarget T>
inline void Texture<T>::storage(int width, int height, GLenum format)
{
    glTextureStorage2D(texture, 1, format, width, height);
}

template<TextureTarget T>
inline void Texture<T>::subImage(int width, int height, GLenum format, GLenum type, const void *pixels)
{
    glTextureSubImage2D(texture, 0, 0, 0, width, height, format, type, pixels);
}

template<TextureTarget T>
inline void Texture<T>::setParameter(GLenum pname, int value)
{
    glTextureParameteri(texture, pname, value);
}

template<TextureTarget T>
inline void Texture<T>::setParameter(GLenum pname, float value)
{
    glTextureParameterf(texture, pname, value);
}

template<TextureTarget T>
inline void Texture<T>::generateMipmap()
{
    glGenerateTextureMipmap(texture);
}

template<TextureTarget T>
inline constexpr GLuint Texture<T>::get() const
{
    return texture;
}
} // namespace thorn::gl
