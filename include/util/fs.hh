/*
 * fs.hh
 * Created: 2021-01-16, 21:14:19.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <common.hh>

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace util
{
const std::string readTextFile(const fs::path &path);
const std::vector<uint8_t> readBinaryFile(const fs::path &path);
void writeTextFile(const fs::path &path, const std::string &str);
} // namespace util
