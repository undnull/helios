#
# CMakeLists.txt
# Created: 2021-03-26, 13:39:17.
# Copyright (C) 2021, Kirill GPRB.
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.10)
project(game VERSION 0.0.1)
add_executable(game "${CMAKE_CURRENT_LIST_DIR}/game.cc")
target_link_libraries(game helios)
