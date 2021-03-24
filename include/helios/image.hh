/*
 * image.hh
 * Created: 2021-03-10, 08:53:03.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <helios/plat/fs.hh>
#include <glad/glad.h>

class Image {
public:
    Image();
    Image(Image &&rhs);
    Image(const Image &rhs) = delete;

    Image &operator=(Image &&rhs);
    Image &operator=(const Image &rhs) = delete;

    virtual ~Image();

    void clear();
    bool loadFromFile(const plat::fs::path &path);

    constexpr int getWidth() const;
    constexpr int getHeight() const;
    constexpr void getSize(int &width, int &height) const;

    constexpr const void *getPixels() const;

public:
    static const GLenum TEXTURE_FORMAT = GL_RGBA;
    static const GLenum TEXTURE_TYPE = GL_UNSIGNED_BYTE;

private:
    int width, height, comp;
    unsigned char *pixels;
};

inline constexpr int Image::getWidth() const
{
    return width;
}

inline constexpr int Image::getHeight() const
{
    return height;
}

inline constexpr void Image::getSize(int &width, int &height) const
{
    width = this->width;
    height = this->height;
}

inline constexpr const void *Image::getPixels() const
{
    return pixels;
}
