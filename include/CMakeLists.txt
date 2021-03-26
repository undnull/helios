#
# CMakeLists.txt
# Created: 2021-01-16, 15:28:02.
# Copyright (C) 2021, Kirill GPRB.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
target_include_directories(helios PUBLIC "${CMAKE_CURRENT_LIST_DIR}")
configure_file("${CMAKE_CURRENT_LIST_DIR}/helios/config.hh.in" "${CMAKE_CURRENT_LIST_DIR}/helios/config.hh" @ONLY)
