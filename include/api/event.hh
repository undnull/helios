/*
 * event.hh
 * Created: 2021-03-23, 10:32:10.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <common.hh>

#include <lua.hpp>

namespace api
{
class Event {
public:
    Event(const char *name);
    void call(lua_State *lua);

public:
    const char *name;
    int ref_id;
    std::vector<int> handlers;
    static Event *base;
    Event *next;
};

inline Event::Event(const char *name) : name(name), ref_id(0), handlers()
{
    next = base;
    base = this;
}

inline void Event::call(lua_State *lua)
{
    lua_rawgeti(lua, LUA_REGISTRYINDEX, ref_id);
    for(const auto &it : handlers) {
        lua_rawgeti(lua, -1, it);
        lua_pcall(lua, 0, 0, 0);
    }
    lua_pop(lua, 1);
}
} // namespace api

#define API_EVENT(var, name)    \
    static api::Event x_api_e_##var(name)

#define API_EVENT_CALL(var, lua)   \
    x_api_e_##var.call(lua)
