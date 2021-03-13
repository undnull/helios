/*
 * vertex.hh
 * Created: 2021-03-05, 12:01:05.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <common.hh>

namespace data
{
struct vertex {
    float2_t position = { 0.0f, 0.0f };
    float2_t texcoord = { 0.0f, 0.0f };
};
} // namespace data
