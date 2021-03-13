#
# CMakeLists.txt
# Created: 2021-01-16, 15:25:33.
# Copyright (C) 2021, Kirill GPRB.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.10)
project(glad VERSION 0.1.34 LANGUAGES C)
add_library(glad STATIC "${CMAKE_CURRENT_LIST_DIR}/glad.c")
target_include_directories(glad PRIVATE "${CMAKE_CURRENT_LIST_DIR}/include/")
target_include_directories(glad PUBLIC "${CMAKE_CURRENT_LIST_DIR}/include/")
