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

namespace hx::util
{
/**
 * @brief Command line parser.
 * 
 */
class Args {
public:
    struct option {
        std::string opt;
        std::string argument;
        bool has_argument;
    };

public:
    /**
     * @brief Constructor
     * 
     */
    Args(int argc, char **argv);

    /**
     * @brief Checks if the option is present.
     * 
     * @param option Option name.
     * @return true if an option is present, false otherwise.
     */
    bool hasOption(const std::string &option) const;

    /**
     * @brief Checks if the option has an argument.
     * 
     * @param option Option name.
     * @return true if an option is present and has an argument, false otherwise.
     */
    bool hasArgument(const std::string &option) const;

    /**
     * @brief Gets an argument of an option.
     * 
     * @param option Option name.
     * @return Argument value or nullptr if option is not present or doesn't have an argument.
     */
    const char *getArgument(const std::string &option) const;

private:
    std::vector<option> options;
};
} // namespace hx::util
