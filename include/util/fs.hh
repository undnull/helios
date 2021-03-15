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
#include <fstream>
#include <iterator>
#include <string>
#include <sstream>
#include <vector>

namespace fs = std::filesystem;

namespace util
{
inline const std::string readTextFile(const fs::path &path)
{
    std::stringstream ss;
    ss << std::ifstream(path, std::ios::in).rdbuf();
    return ss.str();
}

inline const std::vector<uint8_t> readBinaryFile(const fs::path &path)
{
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    ifs.unsetf(std::ios::skipws);

    std::vector<uint8_t> buffer;

    ifs.seekg(0, std::ios::end);
    buffer.reserve(ifs.tellg());
    ifs.seekg(0, std::ios::beg);

    buffer.insert(buffer.begin(), std::istream_iterator<uint8_t>(ifs), std::istream_iterator<uint8_t>());
    return buffer;
}

inline void writeTextFile(const fs::path &path, const std::string &str)
{
    std::ofstream(path, std::ios::out) << str;
}
} // namespace util
