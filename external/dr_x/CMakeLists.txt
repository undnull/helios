#
# CMakeLists.txt
# Created: 2021-03-31, 18:30:56.
# Copyright (C) 2021, Kirill GPRB.
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.10)
project(dr_x VERSION 0.0.0)
add_library(dr_x STATIC "${CMAKE_CURRENT_LIST_DIR}/dr_x.c")
target_include_directories(dr_x PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
