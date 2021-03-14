/*
 * command_line.hh
 * Created: 2021-01-30, 14:49:00
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <common.hh>

namespace util
{
class CommandLine {
public:
    struct option {
        std::string opt;
        std::string argument;
        bool has_argument;
    };

public:
    CommandLine(int argc, char **argv);

    bool hasOption(const char *option) const;
    bool hasArgument(const char *option) const;
    const char *getArgument(const char *option) const;

private:
    std::vector<option> options;
};
} // namespace util
