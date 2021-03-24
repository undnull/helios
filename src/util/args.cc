/*
 * args.cc
 * Created: 2021-01-30, 14:52:00
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <helios/util/args.hh>

namespace util
{
static inline const bool isOption(const char *option)
{
    if(!option || *option != '-')
        return false;
    while(*option)
        option++;
    return option[-1] != '-';
}

Args::Args(int argc, char **argv)
    : options()
{
    for(int i = 1; i < argc; i++) {
        if(isOption(argv[i])) {
            option opt;
            opt.opt = argv[i];
            opt.has_argument = false;
            int j = i + 1;
            if(j < argc && !isOption(argv[j])) {
                opt.has_argument = true;
                opt.argument = argv[j];
                i++;
            }
            options.push_back(opt);
        }
    }
}

bool Args::hasOption(const std::string &opt) const
{
    for(const auto &it : options) {
        if(it.opt == opt)
            return true;
    }
    return false;
}

bool Args::hasArgument(const std::string &opt) const
{
    for(const auto &it : options) {
        if(it.opt == opt && it.has_argument)
            return true;
    }
    return false;
}

const char *Args::getArgument(const std::string &opt) const
{
    for(const auto &it : options) {
        if(it.opt == opt && it.has_argument)
            return it.argument.c_str();
    }
    return nullptr;
}
} // namespace util
