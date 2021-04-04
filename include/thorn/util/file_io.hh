/*
 * file_io.hh
 * Created: 2021-04-03, 12:08:39.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

namespace thorn::util::file_io
{
static inline const std::vector<uint8_t> read(const std::string &path)
{
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    return std::vector<uint8_t>(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
}
} // namespace thorn::util::file_io
