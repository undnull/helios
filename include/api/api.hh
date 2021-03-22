/*
 * api.hh
 * Created: 2021-03-22, 00:14:15.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <common.hh>
#include <util/fs.hh>

#include <lua.hpp>

namespace api
{
class VM {
public:
    VM();
    virtual ~VM();
    constexpr lua_State *get() const;

private:
    lua_State *lua;
    int ref_id;
};

inline constexpr lua_State *VM::get() const
{
    return lua;
}
} // namespace api
