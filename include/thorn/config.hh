/*
 * config.hh
 * Created: whatever_date, whatever_time.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <stdint.h>

namespace thorn
{
static constexpr const int VERSION_MAJOR = 0;
static constexpr const int VERSION_MINOR = 1;
static constexpr const int VERSION_PATCH = 0;
static constexpr const uint32_t GIT_REV = 0x0a37e78f;

static constexpr const char *VERSION_STR = "0.1.0";
static constexpr const char *GIT_REV_STR = "0a37e78f";
} // namespace thorn
