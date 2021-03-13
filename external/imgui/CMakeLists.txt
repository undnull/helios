#
# CMakeLists.txt
# Created: 2021-03-05, 17:28:06.
# Copyright (C) 2021, Kirill GPRB.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.
#
cmake_minimum_required(VERSION 3.10)
project(imgui VERSION 1.81 LANGUAGES CXX)
add_library(imgui INTERFACE)
target_compile_definitions(imgui INTERFACE IMGUI_IMPL_OPENGL_LOADER_GLAD=1)
target_include_directories(imgui INTERFACE "${CMAKE_CURRENT_LIST_DIR}")
target_sources(imgui INTERFACE
    "${CMAKE_CURRENT_LIST_DIR}/imgui_draw.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui_impl_glfw.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui_impl_opengl3.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui_stdlib.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui_tables.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui_widgets.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/imgui.cpp")
