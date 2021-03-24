#
# CMakeLists.txt
# Created: 2021-01-16, 15:41:11.
# Copyright (C) 2021, Kirill GPRB.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
target_sources(helios PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/image.cc"
    "${CMAKE_CURRENT_LIST_DIR}/logger.cc"
    "${CMAKE_CURRENT_LIST_DIR}/main.cc")
add_subdirectory(render)
add_subdirectory(util)
