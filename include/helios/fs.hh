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
#include <helios/macros.hh>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

MERGE_NAMESPACE(hx::fs, std::filesystem);
namespace hx::fs
{
/**
 * @brief Reads a text file to a string.
 * 
 * @param path File path.
 * @return File contents or an empty string.
 */
static inline const std::string readTextFile(const path &path)
{
    std::stringstream ss;
    ss << std::ifstream(path, std::ios::in).rdbuf();
    return ss.str();
}

/**
 * @brief Reads a binary file to a vector<uint8_t>
 * 
 * @param path File path.
 * @return File contents or an empty vector.
 */
static inline const std::vector<uint8_t> readBinaryFile(const path &path)
{
    std::ifstream ifs(path, std::ios::in | std::ios::binary);
    ifs.unsetf(std::ios::skipws);

    std::vector<uint8_t> buffer;

    if(ifs.good()) {
        ifs.seekg(0, std::ios::end);
        buffer.reserve(ifs.tellg());
        ifs.seekg(0, std::ios::beg);
        buffer.insert(buffer.begin(), std::istream_iterator<uint8_t>(ifs), std::istream_iterator<uint8_t>());
    }

    return buffer;
}

/**
 * @brief Writes a text file.
 * 
 * @param path File path.
 * @param str File contents.
 */
static inline void writeTextFile(const path &path, const std::string &str)
{
    std::ofstream(path, std::ios::out) << str;
}
} // namespace hx::plat::fs
