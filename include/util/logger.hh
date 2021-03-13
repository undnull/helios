/*
 * logger.hh
 * Created: 2021-01-16, 21:28:14.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <util/format.hh>

namespace util
{
void log(const std::string &str);

template<typename... Args>
static inline constexpr void log(const std::string &fmt, Args... args)
{
    log(util::format(fmt, args...));
}

template<typename... Args>
static inline constexpr void dlog(const std::string &fmt, Args... args)
{
#ifndef NDEBUG
    log(util::format(fmt, args...));
#endif
}

const std::string &getLastLog();
} // namespace util
