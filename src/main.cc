/*
 * main.cc
 * Created: 2021-01-16, 15:41:47.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <helios/image.hh>
#include <helios/logger.hh>
#include <helios/gl/loader.hh>
#include <helios/plat/clock.hh>
#include <helios/plat/context.hh>
#include <helios/plat/window.hh>
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

static constexpr int MOVE_UP = 1;
static constexpr int MOVE_DOWN = 2;
static constexpr int MOVE_LEFT = 4;
static constexpr int MOVE_RIGHT = 8;

static int move_flags = 0;

static void onKey(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if(action == GLFW_PRESS || action == GLFW_REPEAT) {
        switch(key) {
            case GLFW_KEY_W:
                move_flags |= MOVE_DOWN;
                break;
            case GLFW_KEY_S:
                move_flags |= MOVE_UP;
                break;
            case GLFW_KEY_D:
                move_flags |= MOVE_LEFT;
                break;
            case GLFW_KEY_A:
                move_flags |= MOVE_RIGHT;
                break;
        }
    }
    else {
        switch(key) {
            case GLFW_KEY_W:
                move_flags &= ~MOVE_DOWN;
                break;
            case GLFW_KEY_S:
                move_flags &= ~MOVE_UP;
                break;
            case GLFW_KEY_D:
                move_flags &= ~MOVE_LEFT;
                break;
            case GLFW_KEY_A:
                move_flags &= ~MOVE_RIGHT;
                break;
        }
    }
}

int main(int argc, char **argv)
{
    util::Args args(argc, argv);

    Logger logger;
    logger.log("Logger test");

    PLAT_CREATE_CONTEXT();

    plat::Window window(800, 600, "Window");
    window.makeContextCurrent();

    if(!gl::load()) {
        glfwTerminate();
        return false;
    }

    window.setSwapInterval(1);

    glfwSetKeyCallback(window.get(), onKey);
    glfwSetInputMode(window.get(), GLFW_STICKY_KEYS, GLFW_TRUE);

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(debugCallback, nullptr);

    const unsigned int nvidia_131185 = 131185;
    glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 1, &nvidia_131185, GL_FALSE);

    plat::Clock perf_timer, clock;
    float perf_frametime = 0.0f;

    Image tilemap_img;
    if(!tilemap_img.loadFromFile("assets/textures/tilemap.png"))
        return 1;
    
    Image tileset_img;
    if(!tileset_img.loadFromFile("assets/textures/tileset.png"))
        return 1;

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

    const float tile_size = 16.0f;
    const float2_t tilemap_size = { tilemap_img.getWidth(), tilemap_img.getHeight() };
    const float2_t tileset_size = { tileset_img.getWidth(), tileset_img.getHeight() };

    math::Transform transform;
    transform.setScale(10.0f);

    math::View view;

    render::TilemapRenderer renderer(800, 600);
    renderer.setView(view);

    while(!window.shouldClose()) {
        const float frametime = clock.reset();
        perf_frametime += frametime;
        perf_frametime *= 0.5f;

        if(move_flags) {
            const float speed = 256.0f;
            float2_t velocity = float2_t(0.0f, 0.0f);
            if(move_flags & MOVE_UP)
                velocity.y -= speed;
            if(move_flags & MOVE_DOWN)
                velocity.y += speed;
            if(move_flags & MOVE_RIGHT)
                velocity.x += speed;
            if(move_flags & MOVE_LEFT)
                velocity.x -= speed;
            view.move(velocity * frametime);
            renderer.setView(view);
        }

        if(perf_timer.getTime() >= 1.0f) {
            logger.log("average frametime: %f (%f FPS)", perf_frametime, 1.0f / perf_frametime);
            perf_timer.reset();
        }

        renderer.draw(transform, tilemap_size, tileset_size, tile_size, tilemap, tileset);

        glBindProgramPipeline(0);
        window.swapBuffers();
        window.handleEvents();
    }

    return 0;
}
