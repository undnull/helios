/*
 * format.hh
 * Created: 2021-01-16, 21:24:47.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>

namespace hx::util
{
template<typename... VA>
static inline constexpr const std::string format(const std::string &fmt, VA &&... args)
{
    const int count = snprintf(nullptr, 0, fmt.c_str(), std::forward<VA>(args)...);
    if(count <= 0)
        return fmt;

    std::vector<char> buffer((size_t)count + 1);
    snprintf(buffer.data(), buffer.size(), fmt.c_str(), std::forward<VA>(args)...);

    return std::string(buffer.data());
}
} // namespace hx::util
