/*
 * event.cc
 * Created: 2021-03-23, 10:50:51.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <api/event.hh>
#include <api/module.hh>

namespace api
{
Event *Event::base = nullptr;
} // namespace api

/**
 * API: event.*
 * Implements event system.
 */
API_MODULE(event);

/**
 * API: function event.hook(event: string, handler: function): void
 * Registers a new event handler
 */
API_FUNCTION(event, hook)
{
    const auto top = lua_gettop(lua);
    if(top != 2)
        return luaL_error(lua, "argument error");

    const char *name = luaL_checkstring(lua, 1);
    for(api::Event *event = api::Event::base; event; event = event->next) {
        if(strcmp(event->name, name) == 0) {
            lua_rawgeti(lua, LUA_REGISTRYINDEX, event->ref_id);
            lua_pushvalue(lua, 2);
            event->handlers.push_back(luaL_ref(lua, -2));
            lua_pop(lua, 2);
            return 0;
        }
    }

    return luaL_error(lua, "invalid event %s", name);
}
