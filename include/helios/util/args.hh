/*
 * args.hh
 * Created: 2021-01-30, 14:49:00
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <string>
#include <vector>

namespace util
{
class Args {
public:
    struct option {
        std::string opt;
        std::string argument;
        bool has_argument;
    };

public:
    Args(int argc, char **argv);

    bool hasOption(const std::string &option) const;
    bool hasArgument(const std::string &option) const;
    const char *getArgument(const std::string &option) const;

private:
    std::vector<option> options;
};
} // namespace util
