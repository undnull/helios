/*
 * buffer.hh
 * Created: 2021-03-31, 18:31:54.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <stddef.h>
#include <vector>

namespace hx::sound
{
template<typename T>
class Buffer {
public:
    int getChannelCount() const;
    double getSampleRate() const;
    const std::vector<float> &getSamples() const;
};

template<typename T>
inline int Buffer<T>::getChannelCount() const
{
    return static_cast<const T *>(this)->getChannelCount();
}

template<typename T>
inline double Buffer<T>::getSampleRate() const
{
    return static_cast<const T *>(this)->getSampleRate();
}

template<typename T>
inline const std::vector<float> &Buffer<T>::getSamples() const
{
    return static_cast<const T *>(this)->getSamples();
}
} // namespace hx::sound
