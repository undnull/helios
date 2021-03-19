#
# CMakeLists.txt
# Created: 2021-03-05, 19:45:02.
# Copyright (C) 2021, Kirill GPRB.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
target_sources(helios PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/file_browser.cc"
    "${CMAKE_CURRENT_LIST_DIR}/logger_out.cc"
    "${CMAKE_CURRENT_LIST_DIR}/menu_bar.cc"
    "${CMAKE_CURRENT_LIST_DIR}/ui.cc")
