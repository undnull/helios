/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <helios/gl/loader.hh>
#include <helios/image.hh>
#include <helios/logger.hh>
#include <helios/plat/clock.hh>
#include <helios/plat/context.hh>
#include <helios/plat/window.hh>
#include <helios/render/background_renderer.hh>
#include <helios/render/tilemap_renderer.hh>
#include <helios/util/args.hh>

static void debugCallback(unsigned int src, unsigned int type, unsigned int id, unsigned int severity, int length, const char *msg, const void *arg)
{
    Logger logger("OpenGL");
    switch(severity) {
        case GL_DEBUG_SEVERITY_HIGH:
        case GL_DEBUG_SEVERITY_MEDIUM:
            logger.log(msg);
            break;
        default:
            logger.dlog(msg);
            break;
    }
}

int main(int argc, char **argv)
{
    util::Args args(argc, argv);

    Logger logger;
    logger.log("Logger test");

    PLAT_CREATE_CONTEXT();

    plat::Window window(1152, 648, "Window");
    window.makeContextCurrent();

    if(!gl::load()) {
        glfwTerminate();
        return false;
    }

    window.setSwapInterval(1);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);

    const unsigned int nvidia_131185 = 131185;
    glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 1, &nvidia_131185, GL_FALSE);

    plat::Clock perf_timer, clock;
    float perf_frametime = 0.0f;

    Image bg_img;
    if(!bg_img.loadFromFile("assets/textures/parallax.png"))
        return 1;

    Image tilemap_img;
    if(!tilemap_img.loadFromFile("assets/textures/tilemap.png"))
        return 1;

    Image tileset_img;
    if(!tileset_img.loadFromFile("assets/textures/tileset.png"))
        return 1;

    gl::Texture bg;
    bg.storage(bg_img.getWidth(), bg_img.getHeight(), GL_RGBA16F);
    bg.subImage(bg_img.getWidth(), bg_img.getHeight(), Image::TEXTURE_FORMAT, Image::TEXTURE_TYPE, bg_img.getPixels());
    bg.setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    bg.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    bg.setParameter(GL_TEXTURE_WRAP_S, GL_REPEAT);
    bg.setParameter(GL_TEXTURE_WRAP_T, GL_REPEAT);

    gl::Texture tilemap;
    tilemap.storage(tilemap_img.getWidth(), tilemap_img.getHeight(), GL_RGBA16F);
    tilemap.subImage(tilemap_img.getWidth(), tilemap_img.getHeight(), Image::TEXTURE_FORMAT, Image::TEXTURE_TYPE, tilemap_img.getPixels());
    tilemap.setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    tilemap.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    gl::Texture tileset;
    tileset.storage(tileset_img.getWidth(), tileset_img.getHeight(), GL_RGBA16F);
    tileset.subImage(tileset_img.getWidth(), tileset_img.getHeight(), Image::TEXTURE_FORMAT, Image::TEXTURE_TYPE, tileset_img.getPixels());
    tileset.setParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    tileset.setParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    const float2_t bg_size = { bg_img.getWidth(), bg_img.getHeight() };

    const float tile_size = 16.0f;
    const float2_t tilemap_size = { tilemap_img.getWidth(), tilemap_img.getHeight() };
    const float2_t tileset_size = { tileset_img.getWidth(), tileset_img.getHeight() };

    math::Transform transform;
    transform.setScale(50.0f);

    math::View view;
    view.setSize(float2_t(1152, 648));

    render::BackgroundRenderer background_renderer(1152, 648);
    background_renderer.setView(view);

    render::TilemapRenderer tilemap_renderer(1152, 648);
    tilemap_renderer.setView(view);

    while(!window.shouldClose()) {
        const float frametime = clock.reset();
        perf_frametime += frametime;
        perf_frametime *= 0.5f;

        {
            float2_t velocity = float2_t(0.0f, 0.0f);
            float angle = 0.0f;
            if(glfwGetKey(window.get(), GLFW_KEY_W) == GLFW_PRESS)
                velocity.y += 64.0f;
            if(glfwGetKey(window.get(), GLFW_KEY_S) == GLFW_PRESS)
                velocity.y -= 64.0f;
            if(glfwGetKey(window.get(), GLFW_KEY_D) == GLFW_PRESS)
                velocity.x -= 64.0f;
            if(glfwGetKey(window.get(), GLFW_KEY_A) == GLFW_PRESS)
                velocity.x += 64.0f;
            if(glfwGetKey(window.get(), GLFW_KEY_Q) == GLFW_PRESS)
                angle -= 0.5f;
            if(glfwGetKey(window.get(), GLFW_KEY_E) == GLFW_PRESS)
                angle += 0.5f;
            if(glfwGetKey(window.get(), GLFW_KEY_F1) == GLFW_PRESS)
                view.zoom(1.1f);
            if(glfwGetKey(window.get(), GLFW_KEY_F2) == GLFW_PRESS)
                view.zoom(0.9f);
            view.move(velocity * frametime);
            view.rotate(angle);
            background_renderer.setView(view);
            tilemap_renderer.setView(view);
        }

        if(perf_timer.getTime() >= 1.0f) {
            logger.log("average frametime: %f (%f FPS)", perf_frametime, 1.0f / perf_frametime);
            perf_timer.reset();
        }

        glDisable(GL_BLEND);
        background_renderer.draw(bg, bg_size, float2_t(0.5f, 0.5f));

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        tilemap_renderer.draw(transform, tilemap_size, tileset_size, tile_size, tilemap, tileset);

        glBindProgramPipeline(0);
        window.swapBuffers();
        window.handleEvents();
    }

    return 0;
}
