/*
 * logger.cc
 * Created: 2021-01-16, 21:30:28.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <api/module.hh>
#include <util/logger.hh>

#include <fstream>
#include <iostream>
#include <time.h>

namespace util
{
static std::mutex mutex;
static std::ofstream logfile("./helios.log", std::ios::out | std::ios::app);
static std::ofstream logfile_l("./helios.latest.log", std::ios::out);
static std::string last_log;

void log(const std::string &str)
{
    std::lock_guard<std::mutex> al(mutex);

    char datetime[40] = { 0 };
    time_t cur_time = time(nullptr);
    strftime(datetime, sizeof(datetime), "[%Y-%m-%d, %H:%M:%S]", localtime(&cur_time));

    std::stringstream ss;
    ss << datetime;
    ss << " ";
    ss << str;

    last_log = ss.str();

    std::cerr << last_log << std::endl;
    logfile << last_log << std::endl;
    logfile_l << last_log << std::endl;
}

const std::string &getLastLog()
{
    return last_log;
}
} // namespace util

/**
 * API: logger.*
 * Implements the engine logger for Lua.
 */
API_MODULE(logger);

/**
 * API: function logger.log(...): void
 * Prints something in js-styled way.
 */
API_FUNCTION(logger, log)
{
    const int top = lua_gettop(lua);

    std::stringstream ss;
    for(int i = 1; i <= top; i++) {
        ss << luaL_checkstring(lua, i);
        ss << "\t";
    }

    util::log(ss.str());

    return 0;
}

/**
 * API: function logger.dlog(...): void
 * Prints something in js-styled way if the
 * project is built for debugging.
 */
API_FUNCTION(logger, dlog)
{
#ifndef NDEBUG
    const int top = lua_gettop(lua);

    std::stringstream ss;
    for(int i = 1; i <= top; i++) {
        ss << luaL_checkstring(lua, i);
        ss << "\t";
    }

    util::log(ss.str());
#endif

    return 0;
}
