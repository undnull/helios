/*
 * clock.hh
 * Created: 2021-03-02, 22:55:43.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <GLFW/glfw3.h>

namespace hx::glfw
{
/**
 * @brief Time counter.
 * 
 */
class Clock {
public:
    /**
     * @brief Constructor.
     * 
     * Starts the clock.
     */
    Clock();

    /**
     * @brief Gets the elapsed time.
     * 
     * @return Elapsed time in seconds.
     */
    float getTime() const;

    /**
     * @brief Resets the clock.
     * 
     * @return Elapsed time in seconds.
     */
    float reset();

private:
    float start;
};

inline Clock::Clock()
{
    start = static_cast<float>(glfwGetTime());
}

inline float Clock::getTime() const
{
    return static_cast<float>(glfwGetTime()) - start;
}

inline float Clock::reset()
{
    float cur_time = static_cast<float>(glfwGetTime());
    float delta = cur_time - start;
    start = cur_time;
    return delta;
}
} // namespace hx::plat
