/*
 * vidmode.hh
 * Created: 2021-03-07, 12:47:41.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <util/command_line.hh>
#include <util/fs.hh>
#include <util/json.hh>
#include <util/logger.hh>

struct GLFWmonitor;

namespace data
{
class VidMode {
public:
    VidMode();

    void loadFromJson(const json &j);
    void loadFromArgs(const util::CommandLine &args);

    void saveToFile(const fs::path &path);

    bool loadFromFile(const fs::path &path);

public:
    int width;
    int height;
    int border;
    int swap_interval;
    GLFWmonitor *monitor;
};

inline bool VidMode::loadFromFile(const fs::path &path)
{
    try {
        loadFromJson(json::parse(util::readTextFile(path)));
        return true;
    }
    catch(const std::exception &e) {
        util::log("vidmode: %s", e.what());
        return false;
    }
}
} // namespace data
