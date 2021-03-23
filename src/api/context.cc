/*
 * context.cc
 * Created: 2021-03-22, 00:17:18.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <api/context.hh>
#include <api/event.hh>
#include <api/module.hh>

namespace api
{
static class VM {
public:
    virtual ~VM();
    void demand();
    lua_State *lua = nullptr;
} vm;

VM::~VM()
{
    if(lua)
        lua_close(lua);
}

void VM::demand()
{
    if(!lua) {
        lua = luaL_newstate();
        for(Module *module = Module::base; module; module = module->next) {
            std::vector<luaL_Reg> functions(module->functions);
            functions.push_back(luaL_Reg { nullptr, nullptr });
            lua_createtable(lua, static_cast<int>(functions.size() - 1), 0);
            luaL_setfuncs(lua, functions.data(), 0);
            lua_setglobal(lua, module->name);
        }
        for(Event *event = Event::base; event; event = event->next) {
            lua_newtable(lua);
            event->ref_id = luaL_ref(lua, LUA_REGISTRYINDEX);
        }
    }
}

Context::Context()
{
    vm.demand();
    lua = lua_newthread(vm.lua);
    ref_id = luaL_ref(vm.lua, LUA_REGISTRYINDEX);
}

Context::~Context()
{
    // The Lua thread should be GC'ed after that
    luaL_unref(vm.lua, LUA_REGISTRYINDEX, ref_id);
}
} // namespace api
