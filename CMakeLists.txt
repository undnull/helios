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
project(thorn VERSION 0.1.1)

option(THORN_BUILD_EXAMPLES "Build examples" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(THORN_GIT_REV 0)
add_library(thorn STATIC "")

find_package(Git)
if(GIT_FOUND)
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short=8 HEAD
        WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
        OUTPUT_VARIABLE THORN_GIT_REV
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    message("-- Git revision: ${THORN_GIT_REV}")
endif()

# warning C4996: This function or variable may be unsafe.
target_compile_definitions(thorn PUBLIC _CRT_SECURE_NO_WARNINGS=1)

add_subdirectory(examples)
add_subdirectory(external)
add_subdirectory(include)
add_subdirectory(src)
