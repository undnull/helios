#
# CMakeLists.txt
# Created: 2021-03-03, 19:51:23.
# Copyright (C) 2021, Kirill GPRB.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.10)
project(json VERSION 3.9.1 LANGUAGES CXX)
add_library(json INTERFACE)
target_include_directories(json INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
