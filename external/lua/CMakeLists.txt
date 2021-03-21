#
# CMakeLists.txt
# Created: 2021-03-21, 13:17:08.
# Copyright (C) 2021, Kirill GPRB.
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.10)
project(lua VERSION 5.4.2)
add_library(lua STATIC "")
target_compile_definitions(lua PUBLIC LUA_COMPAT_5_3=1)
target_include_directories(lua PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
target_sources(lua PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/lapi.c"
    "${CMAKE_CURRENT_LIST_DIR}/lcode.c"
    "${CMAKE_CURRENT_LIST_DIR}/lctype.c"
    "${CMAKE_CURRENT_LIST_DIR}/ldebug.c"
    "${CMAKE_CURRENT_LIST_DIR}/ldo.c"
    "${CMAKE_CURRENT_LIST_DIR}/ldump.c"
    "${CMAKE_CURRENT_LIST_DIR}/lfunc.c"
    "${CMAKE_CURRENT_LIST_DIR}/lgc.c"
    "${CMAKE_CURRENT_LIST_DIR}/llex.c"
    "${CMAKE_CURRENT_LIST_DIR}/lmem.c"
    "${CMAKE_CURRENT_LIST_DIR}/lobject.c"
    "${CMAKE_CURRENT_LIST_DIR}/lopcodes.c"
    "${CMAKE_CURRENT_LIST_DIR}/lparser.c"
    "${CMAKE_CURRENT_LIST_DIR}/lstate.c"
    "${CMAKE_CURRENT_LIST_DIR}/lstring.c"
    "${CMAKE_CURRENT_LIST_DIR}/ltable.c"
    "${CMAKE_CURRENT_LIST_DIR}/ltm.c"
    "${CMAKE_CURRENT_LIST_DIR}/lundump.c"
    "${CMAKE_CURRENT_LIST_DIR}/lvm.c"
    "${CMAKE_CURRENT_LIST_DIR}/lzio.c"
    "${CMAKE_CURRENT_LIST_DIR}/lauxlib.c"
    "${CMAKE_CURRENT_LIST_DIR}/lbaselib.c"
    "${CMAKE_CURRENT_LIST_DIR}/lcorolib.c"
    "${CMAKE_CURRENT_LIST_DIR}/ldblib.c"
    "${CMAKE_CURRENT_LIST_DIR}/liolib.c"
    "${CMAKE_CURRENT_LIST_DIR}/lmathlib.c"
    "${CMAKE_CURRENT_LIST_DIR}/loadlib.c"
    "${CMAKE_CURRENT_LIST_DIR}/loslib.c"
    "${CMAKE_CURRENT_LIST_DIR}/lstrlib.c"
    "${CMAKE_CURRENT_LIST_DIR}/ltablib.c"
    "${CMAKE_CURRENT_LIST_DIR}/lutf8lib.c"
    "${CMAKE_CURRENT_LIST_DIR}/linit.c")
