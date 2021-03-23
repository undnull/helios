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

namespace glxx
{
class Texture {
public:
    Texture();
    Texture(Texture &&rhs);
    Texture(const Texture &rhs) = delete;

    virtual ~Texture();

    Texture &operator=(Texture &&rhs);
    Texture &operator=(const Texture &rhs) = delete;

    void storage(int width, int height, GLenum format);
    void subImage(int width, int height, GLenum format, GLenum type, const void *pixels);

    void setParameter(GLenum pname, int value);
    void setParameter(GLenum pname, float value);

    void generateMipmap();

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
} // namespace glxx
