/*
 * ex_demo.cc
 * Created: 2021-04-01, 22:29:37.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <thorn/config.hh>
#include <thorn/context.hh>
#include <thorn/glad.hh>
#include <thorn/glfw/clock.hh>
#include <thorn/glfw/window.hh>
#include <thorn/image.hh>
#include <thorn/render/background_renderer.hh>
#include <thorn/render/tilemap_renderer.hh>
#include <thorn/util/file_io.hh>
#include <iostream>
#include <stdio.h>

constexpr const int WIDTH = 1152;
constexpr const int HEIGHT = 648;

constexpr const float C_SPEED = 128.0f; // 128 pixels/second
constexpr const float R_SPEED = 45.0f;  // 45 degrees/second
constexpr const float Z_SPEED = 0.01f;  // A zoom factor

struct background {
    float2_t scroll;
    float2_t size;
    thorn::gl::Texture2D texture;
};

struct tileset {
    float tile;
    float2_t size;
    thorn::gl::Texture2D texture;
};

struct tilemap {
    thorn::math::Transform t;
    float2_t size;
    thorn::gl::Texture2D texture;
};

static bool loadTexture(const char *path, bool repeat, bool filter, thorn::gl::Texture2D &texture, float2_t &size)
{
    thorn::Image img;
    if(img.load(thorn::util::file_io::read(path))) {
        int width, height;
        img.getSize(width, height);

        size = float2_t(width, height);

        texture.storage(width, height, GL_RGBA16F);
        texture.subImage(width, height, thorn::Image::TEXTURE_FORMAT, thorn::Image::TEXTURE_TYPE, img.getPixels());

        if(repeat) {
            texture.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
            texture.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);
        }
        else {
            texture.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            texture.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        }

        if(filter) {
            texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else {
            texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        return true;
    }

    return false;
}

int main(int argc, char **argv)
{
    THORN_INIT();

    thorn::glfw::Window window(WIDTH, HEIGHT, "App");
    window.makeContextCurrent();

    if(!thorn::glad::load()) {
        std::cerr << "Failed to load GL" << std::endl;
        return 1;
    }

    thorn::Image icon;
    if(icon.load(thorn::util::file_io::read("assets/textures/icon.png")))
        window.setIcon(icon);

    std::cout << "Hello, Thorn!" << std::endl;
    std::cout << "Thorn " << thorn::VERSION_STR << "-" << thorn::GIT_REV_STR << std::endl;

    // Setup the background
    background bg;
    bg.scroll = float2_t(0.5f, 0.5f);
    if(!loadTexture("assets/textures/parallax.png", true, false, bg.texture, bg.size))
        return 1;

    // Setup the tileset.
    tileset ts;
    ts.tile = 16.0f;
    if(!loadTexture("assets/textures/tileset.png", true, false, ts.texture, ts.size))
        return 1;

    // Setup the tilemap
    tilemap tm;
    tm.t.setScale(25.0f);
    if(!loadTexture("assets/textures/tilemap.png", true, false, tm.texture, tm.size))
        return 1;

    thorn::math::View view;
    view.setSize(float2_t(WIDTH, HEIGHT) * 0.5f);

    thorn::render::BackgroundRenderer bg_renderer;
    bg_renderer.loadDefaultShader<thorn::gl::ShaderStage::VERTEX>();
    bg_renderer.loadDefaultShader<thorn::gl::ShaderStage::FRAGMENT>();
    bg_renderer.setView(view);

    thorn::render::TilemapRenderer map_renderer;
    map_renderer.loadDefaultShader<thorn::gl::ShaderStage::VERTEX>();
    map_renderer.loadDefaultShader<thorn::gl::ShaderStage::FRAGMENT>();
    map_renderer.setView(view);

    window.setSwapInterval(1);

    window.on_window_size = [&](int width, int height) {
        view.setSize(float2_t(width, height) * 0.5f);

        bg_renderer.setView(view);
        map_renderer.setView(view);

        glViewport(0, 0, width, height);
    };

    thorn::glfw::Clock clock;

    while(!window.shouldClose()) {
        const float frametime = clock.reset();

        // Handle some inputs
        {
            float2_t cv = float2_t(0.0f, 0.0f);
            float rv = 0.0f;

            // Camera movement
            if(window.isKeyPressed(GLFW_KEY_W))
                cv.y += C_SPEED;
            if(window.isKeyPressed(GLFW_KEY_S))
                cv.y -= C_SPEED;
            if(window.isKeyPressed(GLFW_KEY_D))
                cv.x -= C_SPEED;
            if(window.isKeyPressed(GLFW_KEY_A))
                cv.x += C_SPEED;

            // Camera rotation
            if(window.isKeyPressed(GLFW_KEY_Q))
                rv += R_SPEED;
            if(window.isKeyPressed(GLFW_KEY_E))
                rv -= R_SPEED;

            // Camera zoom
            if(window.isKeyPressed(GLFW_KEY_F1))
                view.zoom((1.0f + Z_SPEED));
            if(window.isKeyPressed(GLFW_KEY_F2))
                view.zoom(1.0f / (1.0f + Z_SPEED));

            if(window.isKeyJustPressed(GLFW_KEY_ESCAPE))
                std::cout << "Escape press!" << std::endl;
            if(window.isKeyJustReleased(GLFW_KEY_ESCAPE))
                std::cout << "Escape release!" << std::endl;

            // Update the view itself
            view.move(cv * frametime);
            view.rotate(rv * frametime);

            // "Tell" renderers that the
            // view has been updated
            bg_renderer.setView(view);
            map_renderer.setView(view);
        }

        // Draw the background layer
        // False means that the background texture won't
        // be fit to the screen (or target) height.
        glDisable(GL_BLEND);
        bg_renderer.draw(bg.texture, bg.size, bg.scroll, false);

        // Draw the tilemap layer
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        map_renderer.draw(tm.t, tm.size, ts.size, ts.tile, tm.texture, ts.texture);

        // Make sure we don't have any pipelines bound
        // so third-party overlay programs won't break
        glBindProgramPipeline(0);

        window.swapBuffers();
        window.handleEvents();
    }

    return 0;
}
