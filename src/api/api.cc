/*
 * api.cc
 * Created: 2021-03-22, 00:17:18.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <api/api.hh>
#include <api/function.hh>
#include <util/logger.hh>

namespace api
{
void init(lua_State *lua)
{
    for(Function *fn = Function::base; fn; fn = fn->next) {
        lua_pushcfunction(lua, fn->func);
        lua_setglobal(lua, fn->name);
    }
}

bool execFile(lua_State *lua, const fs::path &path)
{
    if(fs::exists(path)) {
        const std::string &s = util::readTextFile(path);
        if(luaL_dostring(lua, s.c_str()) != LUA_OK) {
            util::log("api: %s", lua_tostring(lua, -1));
            return false;
        }
        return true;
    }
    return false;
}

/**
 * API  function include(path: string): void
 * An alternative to Lua's dofile() that utilizes
 * the engine-specific paths
 */
API_FUNCTION(include)
{
    const int narg = lua_gettop(lua);
    if(narg != 1)
        return luaL_error(lua, "invalid argument count: %d", narg);
    if(!execFile(lua, lua_tostring(lua, 1)))
        return luaL_error(lua, "api::execFile failed");
    return 0;
}
} // namespace api
