/*
 * menu_bar.cc
 * Created: 2021-03-05, 22:07:53.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <config.hh>
#include <ui/menu_bar.hh>
#include <util/clock.hh>

#include <GLFW/glfw3.h>

namespace ui
{
MenuBar::MenuBar()
{
    file_open = false;
    file_close = false;
    file_new = false;
    file_save = false;
    file_save_as = false;
    file_exit = false;

    view_fps = true;

    fps_framerate = 0.0f;
    fps_frametime = 0.0f;
}

void MenuBar::draw(const ImGuiIO &io)
{
    if(fps_clock.getTime() >= 0.025f) {
        fps_framerate += io.Framerate;
        fps_framerate *= 0.5f;
        fps_frametime += io.DeltaTime * 1000.0f;
        fps_frametime *= 0.5f;
        fps_clock.reset();
    }

    if(ImGui::BeginMainMenuBar()) {
        if(ImGui::BeginMenu("File")) {
            file_open = ImGui::MenuItem("Open", "(WIP)", false, false);
            file_close = ImGui::MenuItem("Close", "(WIP)", false, false);
            ImGui::Separator();
            file_new = ImGui::MenuItem("New", "(WIP)", false, false);
            ImGui::Separator();
            file_exit = ImGui::MenuItem("Exit", "Shift+Esc");
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("View")) {
            ImGui::MenuItem("FPS counter", nullptr, &view_fps);
            ImGui::EndMenu();
        }

        if(ImGui::BeginMenu("Help")) {
            ImGui::MenuItem("helios " VERSION_STRING, nullptr, false, false);
            ImGui::EndMenu();
        }

        if(view_fps) {
            ImGui::SameLine(ImGui::GetWindowWidth() - ImGui::CalcTextSize("DDDD.ddd ms/frame (DDDD.dd FPS)").x * 1.025f);
            ImGui::Text("%4.03f ms/frame (%4.02f FPS)", fps_frametime, fps_framerate);
        }

        ImGui::EndMainMenuBar();
    }

    file_exit = file_exit || (io.KeyShift && io.KeysDown[GLFW_KEY_ESCAPE]);
}
} // namespace ui
