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
#include <glad/glad.h>
#include <utility>

namespace thorn::gl
{
/**
 * @brief Chunk of GPU memory to store image data.
 * 
 */
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
    Texture(Texture &&rhs);
    Texture(const Texture &rhs) = delete;

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
    Texture &operator=(Texture &&rhs);
    Texture &operator=(const Texture &rhs) = delete;

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

inline Texture::Texture()
{
    glCreateTextures(GL_TEXTURE_2D, 1, &texture);
}

inline Texture::Texture(Texture &&rhs)
{
    texture = rhs.texture;
    rhs.texture = 0;
}

inline Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}

inline Texture &Texture::operator=(Texture &&rhs)
{
    Texture copy(std::move(rhs));
    std::swap(copy.texture, texture);
    return *this;
}

inline void Texture::storage(int width, int height, GLenum format)
{
    glTextureStorage2D(texture, 1, format, width, height);
}

inline void Texture::subImage(int width, int height, GLenum format, GLenum type, const void *pixels)
{
    glTextureSubImage2D(texture, 0, 0, 0, width, height, format, type, pixels);
}

inline void Texture::setParameter(GLenum pname, int value)
{
    glTextureParameteri(texture, pname, value);
}

inline void Texture::setParameter(GLenum pname, float value)
{
    glTextureParameterf(texture, pname, value);
}

inline void Texture::generateMipmap()
{
    glGenerateTextureMipmap(texture);
}

inline constexpr GLuint Texture::get() const
{
    return texture;
}
} // namespace thorn::gl
