/*
 * lua.cc
 * Created: 2021-03-21, 13:25:28.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <util/logger.hh>
#include <util/lua.hh>

namespace util
{
static int l_log(lua_State *L)
{
    std::stringstream ss;

    const int top = lua_gettop(L);
    for(int i = 0; i < top; i++) {
        ss << lua_tostring(L, i + 1);
        ss << "\t";
    }

    const std::string &msg = ss.str();
    log("%s", msg.c_str());

    return 0;
}

static int l_dlog(lua_State *L)
{
#ifndef NDEBUG
    std::stringstream ss;

    const int top = lua_gettop(L);
    for(int i = 0; i < top; i++) {
        ss << lua_tostring(L, i + 1);
        ss << "\t";
    }

    const std::string &msg = ss.str();
    log("%s", msg.c_str());
#endif

    return 0;
}

void registerEngineAPI(lua_State *L)
{
    lua_pushcfunction(L, l_log);
    lua_setglobal(L, "log");

    lua_pushcfunction(L, l_dlog);
    lua_setglobal(L, "dlog");
}
} // namespace util
