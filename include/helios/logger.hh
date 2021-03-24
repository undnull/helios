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
#include <helios/util/format.hh>
#include <fstream>
#include <mutex>

class Logger {
public:
    void log(const std::string &str);

    template<typename... VA>
    constexpr void log(const std::string &fmt, VA &&... args);

    template<typename... VA>
    constexpr void dlog(const std::string &fmt, VA &&... args);

private:
    static std::mutex mutex;
    static std::ofstream logfile;
    static std::ofstream logfile_last;
};

template<typename... VA>
inline constexpr void Logger::log(const std::string &fmt, VA &&... args)
{
    log(util::format(fmt, std::forward<VA>(args)...));
}

template<typename... VA>
inline constexpr void Logger::dlog(const std::string &fmt, VA &&... args)
{
#ifndef NDEBUG
    log(util::format(fmt, std::forward<VA>(args)...));
#endif
}
