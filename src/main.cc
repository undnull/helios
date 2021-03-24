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
#include <helios/render/sprite_renderer.hh>
#include <helios/util/args.hh>

static void debugCallback(unsigned int src, unsigned int type, unsigned int id, unsigned int severity, int length, const char *msg, const void *arg)
{
    Logger logger("gl");
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

    plat::Window window(800, 600, "Window");
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

    // All the GL-related (objects) stuff should be done
    // inside of this scope to avoid destructor calls when
    // the window is destroyed and the GL context is gone
    {
        // sprite
        struct {
            float2_t size;
            gl::Texture texture;
            math::Transform transform;
        } sprite;

        Image image;
        if(!image.loadFromFile("assets/textures/bruh.jpg"))
            return false;

        int width, height;
        image.getSize(width, height);

        sprite.size = float2_t(100.0f, 100.0f);

        sprite.texture.storage(width, height, GL_RGBA16F);
        sprite.texture.subImage(width, height, Image::TEXTURE_FORMAT, Image::TEXTURE_TYPE, image.getPixels());
        sprite.texture.setParameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        sprite.texture.setParameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        sprite.texture.setParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        sprite.texture.setParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        sprite.transform.setOrigin(float2_t(50.0f, 50.0f));

        std::vector<math::Transform> transforms;

        // Sprite #1
        sprite.transform.setPosition(float2_t(100.0f, 100.0f));
        transforms.push_back(sprite.transform);

        // Sprite #2
        sprite.transform.setPosition(float2_t(250.0f, 100.0f));
        transforms.push_back(sprite.transform);

        // Sprite #3
        sprite.transform.setPosition(float2_t(400.0f, 100.0f));
        transforms.push_back(sprite.transform);

        // Sprite #4
        transforms.push_back(sprite.transform);

        // Sprite #5 = 2, 3 and 4 combined
        transforms.push_back(sprite.transform);

        render::SpriteRenderer sprite_renderer(800, 600);

        math::View view;
        sprite_renderer.setView(view);

        //ui::init(window);
        //ui::LoggerOut logger_out;
        //ui::MenuBar menu_bar;

        plat::Clock clock;
        float sincos_angle = 0.0f;

        plat::Clock perf;
        float perf_frametime = 0.0f;

        while(!window.shouldClose()) {
            const float frametime = clock.reset();
            perf_frametime += frametime;
            perf_frametime *= 0.5f;

            if(perf.getTime() >= 1.0f) {
                logger.log("average frametime: %f (%f FPS)", perf_frametime, 1.0f / perf_frametime);
                perf.reset();
            }

            transforms[0].rotate(90.0f * frametime);
            transforms[1].rotate(90.0f * frametime * cos(sincos_angle));
            transforms[2].setScale(sin(sincos_angle));
            transforms[3].setPosition(float2_t(550.0f, 100.0f) + 42.0f * float2_t(sin(sincos_angle), cos(sincos_angle)));
            //transforms[3].move(50.0f * float2_t(sin(sincos_angle), cos(sincos_angle)));

            transforms[4].rotate(90.0f * frametime * cos(sincos_angle));
            transforms[4].setScale(sin(sincos_angle));
            transforms[4].setPosition(float2_t(250.0f, 350.0f) + 75.0f * float2_t(sin(sincos_angle), cos(sincos_angle)));
            //transforms[4].move(50.0f * float2_t(sin(sincos_angle), cos(sincos_angle)));

            sincos_angle += frametime;

            glClear(GL_COLOR_BUFFER_BIT);
            glUseProgram(0);

            sprite_renderer.draw(transforms, sprite.texture, sprite.size);

            //const ImGuiIO &io = ui::beginFrame();
            //logger_out.draw(io);
            //menu_bar.draw(io);
            //ui::endFrame();

            //if(menu_bar.file_exit) {
            //    glfwSetWindowShouldClose(window, GLFW_TRUE);
            //    menu_bar.file_exit = false;
            //}

            glBindProgramPipeline(0);
            window.swapBuffers();
            window.handleEvents();
        }
    }

    return 0;
}
