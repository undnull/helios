#
# CMakeLists.txt
# Created: 2021-04-05, 15:50:39.
# Copyright (C) 2021, Kirill GPRB.
# 
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
if(THORN_BUILD_EXAMPLES)
    function(add_executable_example target_name)
        add_executable(${target_name} "${CMAKE_CURRENT_LIST_DIR}/ex_${target_name}.cc")
        target_link_libraries(${target_name} thorn)
    endfunction()
    add_executable_example(demo)
    add_executable_example(blue_window)
endif()
