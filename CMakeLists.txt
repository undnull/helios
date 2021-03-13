#
# CMakeLists.txt
# Created: 2021-01-16, 15:11:18.
# Copyright (C) 2021, Kirill GPRB.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.10)
project(voxelius VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(voxelius "")

# warning C4996: This function or variable may be unsafe.
target_compile_definitions(voxelius PRIVATE _CRT_SECURE_NO_WARNINGS=1)

add_subdirectory(external)
add_subdirectory(include)
add_subdirectory(src)
