#
# CMakeLists.txt
# Created: 2021-03-22, 00:24:00.
# Copyright (C) 2021, Kirill GPRB.
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
target_sources(helios PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/context.cc"
    "${CMAKE_CURRENT_LIST_DIR}/core.cc"
    "${CMAKE_CURRENT_LIST_DIR}/event.cc"
    "${CMAKE_CURRENT_LIST_DIR}/module.cc")
