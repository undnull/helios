/*
 * image.cc
 * Created: 2021-03-24, 10:05:17.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <helios/image.hh>
#include <stb_image.h>

namespace hx
{
Image::Image()
{
    width = -1;
    height = -1;
    comp = -1;
    pixels = nullptr;
}

Image::Image(Image &&rhs)
{
    width = rhs.width;
    height = rhs.height;
    comp = rhs.comp;
    pixels = rhs.pixels;
    rhs.width = -1;
    rhs.height = -1;
    rhs.comp = -1;
    rhs.pixels = nullptr;
}

Image::~Image()
{
    stbi_image_free(pixels);
}

Image &Image::operator=(Image &&rhs)
{
    Image copy(std::move(rhs));
    std::swap(copy.width, width);
    std::swap(copy.height, height);
    std::swap(copy.comp, comp);
    std::swap(copy.pixels, pixels);
    return *this;
}

void Image::clear()
{
    stbi_image_free(pixels);
    width = -1;
    height = -1;
    comp = -1;
    pixels = nullptr;
}

bool Image::loadFromFile(const fs::path &path)
{
    stbi_image_free(pixels);
    pixels = stbi_load(path.string().c_str(), &width, &height, &comp, STBI_rgb_alpha);
    return !!pixels;
}
} // namespace hx
