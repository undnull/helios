#
# CMakeLists.txt
# Created: 2021-04-01, 22:29:44.
# Copyright (C) 2021, Kirill GPRB.
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.10)
project(demo VERSION 1.0.0)
add_executable(demo "${CMAKE_CURRENT_LIST_DIR}/demo.cc")
target_link_libraries(demo thorn)
