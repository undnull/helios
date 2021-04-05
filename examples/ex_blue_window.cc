/*
 * ex_blue_window.cc
 * Created: 2021-04-05, 15:50:48.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <thorn/config.hh>
#include <thorn/context.hh>
#include <thorn/glad.hh>
#include <thorn/glfw/window.hh>
#include <iostream>

int main()
{
    // Create a new Thorn context.
    // Context is an abstraction that initializes
    // all the libraries that should be initialized.
    // This should be called only once in the begining
    // of an entry point of your application.
    THORN_INIT();

    // Open a new window
    thorn::glfw::Window window(800, 600, "Thorn Example!");

    // Load OpenGL
    window.makeContextCurrent();
    if(!thorn::glad::load()) {
        std::cerr << "Failed to load OpenGL" << std::endl;
        return 1;
    }

    // VSync
    window.setSwapInterval(1);

    // Main loop
    while(!window.shouldClose()) {
        // Exit if ESC is pressed
        if(window.isKeyJustPressed(GLFW_KEY_ESCAPE))
            window.setShouldClose(true);

        // Clear the screen
        glClearColor(0.0f, 0.0f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // End frame
        window.swapBuffers();
        window.handleEvents();
    }

    return 0;
}
