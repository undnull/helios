/*
 * module.hh
 * Created: 2021-03-22, 14:10:34.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <api/api.hh>

namespace api
{
class Module {
public:
    Module(const char *name);

public:
    const char *name;
    std::vector<luaL_Reg> functions;
    static Module *base;
    Module *next;
};

class Function {
public:
    Function(Module &m, const char *name, lua_CFunction func);
};

inline Module::Module(const char *name) : name(name), functions()
{
    next = base;
    base = this;
}

inline Function::Function(Module &m, const char *name, lua_CFunction func)
{
    m.functions.push_back(luaL_Reg { name, func });
}
} // namespace api

#define API_MODULE(module)                                                          \
    static api::Module x_api_m_##module(#module)

#define API_FUNCTION(module, name)                                                  \
    static int x_api_c_##name(lua_State *lua);                                      \
    static api::Function x_api_f_##name(x_api_m_##module, #name, x_api_c_##name);   \
    static int x_api_c_##name(lua_State *lua)
