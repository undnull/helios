/*
 * logger.cc
 * Created: 2021-01-16, 21:30:28.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <helios/logger.hh>
#include <iostream>
#include <time.h>
#include <sstream>

namespace hx
{
std::mutex Logger::mutex;
std::ofstream Logger::logfile("./helios.log", std::ios::out | std::ios::app);
std::ofstream Logger::logfile_last("./helios.latest.log", std::ios::out);

void Logger::log(const std::string &str)
{
    std::lock_guard<std::mutex> al(mutex);

    char datetime[40] = { 0 };
    time_t cur_time = time(nullptr);
    strftime(datetime, sizeof(datetime), "[%Y-%m-%d, %H:%M:%S]", localtime(&cur_time));

    std::stringstream ss;

    ss << datetime;
    ss << " ";

    if(source) {
        ss << source;
        ss << ": ";
    }

    ss << str;

    std::cerr << ss.str() << std::endl;
    logfile << ss.str() << std::endl;
    logfile_last << ss.str() << std::endl;
}
} // namespace hx
