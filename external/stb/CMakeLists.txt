#
# CMakeLists.txt
# Created: 2021-01-20, 14:13:11.
# Copyright (C) 2021, Kirill GPRB.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.10)
project(stb VERSION 1.3.3.7 LANGUAGES C)
add_library(stb STATIC "${CMAKE_CURRENT_LIST_DIR}/stb.c")
target_include_directories(stb PRIVATE "${CMAKE_CURRENT_LIST_DIR}/stb/")
target_include_directories(stb PUBLIC "${CMAKE_CURRENT_LIST_DIR}/stb/")
