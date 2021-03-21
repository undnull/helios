/*
 * function.hh
 * Created: 2021-03-22, 00:11:24.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <lua.hpp>

namespace api
{
class Function {
public:
    Function(const char *name, lua_CFunction func);

public:
    static Function *base;
    Function *next;

public:
    const char *name;
    lua_CFunction func;
};

inline Function::Function(const char *name, lua_CFunction func)
{
    next = base;
    base = this;
    this->name = name;
    this->func = func;
}
} // namespace api

#define API_FUNCTION(name)                                          \
    static int __apifn_##name(lua_State *lua);                      \
    static const api::Function __api_##name(#name, __apifn_##name); \
    static int __apifn_##name(lua_State *lua)
