/*
 * core.cc
 * Created: 2021-03-22, 14:58:47.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <api/core.hh>
#include <api/module.hh>

namespace api
{
bool include(lua_State *lua, const fs::path &path)
{
    if(fs::exists(path)) {
        const std::string &src = util::readTextFile(path);
        if(luaL_dostring(lua, src.c_str()) == LUA_OK)
            return true;
    }
    return false;
}
} // namespace api

/**
 * API: core.*
 * Implements core Lua functions using the
 * internal engine functionality.
 */
API_MODULE(core);

/**
 * API: function core.include(path: string): void
 * A Lua's dofile() replacement.
 */
API_FUNCTION(core, include)
{
    const int top = lua_gettop(lua);
    if(top == 1) {
        if(api::include(lua, lua_tostring(lua, 1)))
            return 0;
        return luaL_error(lua, "api::include() failed");
    }
    return luaL_error(lua, "argument error");
}

/**
 * API: function core.shutdown(core: integer): void
 * Exits the application.
 */
API_FUNCTION(core, shutdown)
{
    const int top = lua_gettop(lua);
    if(top == 1) {
        exit(static_cast<int>(luaL_checkinteger(lua, 1)));
        return 0;
    }
    return luaL_error(lua, "argument error");
}
