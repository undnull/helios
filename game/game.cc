/*
 * game.cc
 * Created: 2021-03-26, 13:39:49.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 * 
 * This is a test game to make sure everything I wrote works as
 * intended and doesn't break. This file will change over time as
 * new features are added or old features are removed.
 */
#include <helios/glfw/clock.hh>
#include <helios/glfw/context.hh>
#include <helios/glfw/window.hh>
#include <helios/gl/framebuffer.hh>
#include <helios/gl/loader.hh>
#include <helios/config.hh>
#include <helios/image.hh>
#include <helios/logger.hh>
#include <helios/types.hh>
#include <helios/render/background_renderer.hh>
#include <helios/render/blit_renderer.hh>
#include <helios/render/tilemap_renderer.hh>

#include <portaudio.h>

constexpr const int WIDTH = 1152;
constexpr const int HEIGHT = 648;

constexpr const float C_SPEED = 128.0f; // 128 pixels/second
constexpr const float R_SPEED = 45.0f;  // 45 degrees/second
constexpr const float Z_SPEED = 0.01f;  // A zoom factor

struct background {
    float2_t scroll;
    float2_t size;
    hx::gl::Texture texture;
};

struct tileset {
    float tile;
    float2_t size;
    hx::gl::Texture texture;
};

struct tilemap {
    hx::math::Transform t;
    float2_t size;
    hx::gl::Texture texture;
};

static bool loadTexture(const hx::fs::path &path, bool repeat, bool filter, hx::gl::Texture &texture, float2_t &size)
{
    hx::Image img;
    if(img.loadFromFile(path)) {
        int width, height;
        img.getSize(width, height);

        size = float2_t(width, height);

        texture.storage(width, height, GL_RGBA16F);
        texture.subImage(width, height, hx::Image::TEXTURE_FORMAT, hx::Image::TEXTURE_TYPE, img.getPixels());

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

struct pa_data {
    float left;
    float right;
};

static int paCallback(const void *in, void *out, unsigned long frames, const PaStreamCallbackTimeInfo *time_info, PaStreamCallbackFlags flags, void *data)
{
    pa_data *p_data = reinterpret_cast<pa_data *>(data);
    float *f_out = reinterpret_cast<float *>(out);
    for(unsigned long i = 0; i < frames; i++) {
        *f_out++ = p_data->left * 0.1f;
        *f_out++ = p_data->right * 0.1f;

        p_data->left += 0.01f;
        p_data->right += 0.01f;

        if(p_data->left >= 1.0f)
            p_data->left -= 2.0f;
        if(p_data->right >= 1.0f)
            p_data->right -= 2.0f;
    }
    return 0;
}

int main()
{
    hx::Logger alogger("PortAudio");

    // PortAudio test
    PaError err;
    
    err = Pa_Initialize();
    if(err != paNoError) {
        alogger.log("PA: %s", Pa_GetErrorText(err));
        return 1;
    }

    pa_data data;
    data.left = -1.0f;
    data.right = -1.0f;

    PaStream *stream;
    err = Pa_OpenDefaultStream(&stream, 0, 2, paFloat32, 44100, paFramesPerBufferUnspecified, paCallback, &data);
    if(err != paNoError) {
        alogger.log("PA: %s", Pa_GetErrorText(err));
        return 1;
    }

    err = Pa_StartStream(stream);
    if(err != paNoError) {
        alogger.log("PA: %s", Pa_GetErrorText(err));
        return 1;
    }

    Pa_Sleep(1000);
    err = Pa_StopStream(stream);
    if(err != paNoError) {
        alogger.log("PA: %s", Pa_GetErrorText(err));
        return 1;
    }

    err = Pa_CloseStream(stream);
    if(err != paNoError) {
        alogger.log("PA: %s", Pa_GetErrorText(err));
        return 1;
    }

    err = Pa_Terminate();
    if(err != paNoError) {
        alogger.log("PA: %s", Pa_GetErrorText(err));
        return 1;
    }

    // Initialize GLFW
    HX_CREATE_GLFW_CONTEXT();

    // Create a new logger instance
    // for the game
    hx::Logger logger("Game");
    logger.log("Hello, Helios!");
    logger.log("Using Helios %s", hx::VERSION);

    // Create a new window
    hx::glfw::Window window(WIDTH, HEIGHT, "Game");
    window.makeContextCurrent();

    // Load GL
    if(!hx::gl::load()) {
        logger.log("Failed to load GL");
        return 1;
    }

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

    // Unlike SFML view is required to be set up
    // so setup the view
    hx::math::View view;
    view.setSize(float2_t(WIDTH, HEIGHT) * 0.5f);

    // Setup the background renderer
    hx::render::BackgroundRenderer bg_renderer;
    bg_renderer.setView(view);
    
    // Setup the tilemap renderer
    hx::render::TilemapRenderer tm_renderer;
    tm_renderer.setView(view);

    // Blit renderer allows rendering of
    // full-frame textured quads
    hx::render::BlitRenderer blit_renderer;

    // Enable VSync
    window.setSwapInterval(1);

    window.on_resize = [&](int width, int height) {
        view.setSize(float2_t(width, height) * 0.5f);

        bg_renderer.setView(view);
        tm_renderer.setView(view);

        glViewport(0, 0, width, height);
    };

    // To move the camera correctly we need
    // to know the frametime (delta time)
    hx::glfw::Clock clock;

    // Game loop
    while(!window.shouldClose()) {
        const float frametime = clock.reset();

        // Handle some inputs
        {
            float2_t cv = float2_t(0.0f, 0.0f);
            float rv = 0.0f;

            // Camera movement
            if(glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
                cv.y += C_SPEED;
            if(glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS)
                cv.y -= C_SPEED;
            if(glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
                cv.x -= C_SPEED;
            if(glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
                cv.x += C_SPEED;
            
            // Camera rotation
            if(glfwGetKey(window.get(), GLFW_KEY_Q) == GLFW_PRESS)
                rv += R_SPEED;
            if(glfwGetKey(window.get(), GLFW_KEY_E) == GLFW_PRESS)
                rv -= R_SPEED;

            // Camera zoom
            if(glfwGetKey(window.get(), GLFW_KEY_F1) == GLFW_PRESS)
                view.zoom((1.0f + Z_SPEED));
            if(glfwGetKey(window.get(), GLFW_KEY_F2) == GLFW_PRESS)
                view.zoom(1.0f / (1.0f + Z_SPEED));

            // Update the view itself
            view.move(cv * frametime);
            view.rotate(rv * frametime);

            // "Tell" renderers that the
            // view has been updated
            bg_renderer.setView(view);
            tm_renderer.setView(view);
        }

        // Draw the background layer
        // False means that the background texture won't
        // be fit to the screen (or target) height.
        glDisable(GL_BLEND);
        bg_renderer.draw(bg.texture, bg.size, bg.scroll, false);
        
        // Draw the tilemap layer
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        tm_renderer.draw(tm.t, tm.size, ts.size, ts.tile, tm.texture, ts.texture);

        // Make sure we don't have any pipelines bound
        // so third-party overlay programs won't break
        glBindProgramPipeline(0);

        window.swapBuffers();
        window.handleEvents();
    }

    return 0;
}
