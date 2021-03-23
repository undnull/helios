#
# CMakeLists.txt
# Created: 2021-01-16, 15:15:01.
# Copyright (C) 2021, Kirill GPRB.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

if(POLICY CMP0079)
    cmake_policy(SET CMP0079 NEW)
endif()

add_subdirectory(glad)
target_link_libraries(helios glad)

add_subdirectory(glfw)
target_link_libraries(helios glfw)
target_compile_definitions(helios PRIVATE GLFW_INCLUDE_NONE=1)

add_subdirectory(glm)
target_link_libraries(helios glm)

add_subdirectory(imgui)
target_link_libraries(helios imgui)

add_subdirectory(json)
target_link_libraries(helios json)

add_subdirectory(stb)
target_link_libraries(helios stb)
