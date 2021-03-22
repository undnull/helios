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
#include <api/module.hh>

namespace api
{
void init(lua_State *lua)
{
    for(Module *module = Module::base; module; module = module->next) {
        std::vector<luaL_Reg> functions(module->functions);
        functions.push_back(luaL_Reg { nullptr, nullptr });
        lua_createtable(lua, static_cast<int>(functions.size() - 1), 0);
        luaL_setfuncs(lua, functions.data(), 0);
        lua_setglobal(lua, module->name);
    }
}
} // namespace api
