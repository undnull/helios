/*
 * context.hh
 * Created: 2021-03-31, 21:01:00.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <exception>
#include <portaudio.h>

namespace hx::sound
{
class Context {
public:
    Context();
    virtual ~Context();
};

inline Context::Context()
{
    if(Pa_Initialize() != paNoError)
        std::terminate();
}

inline Context::~Context()
{
    Pa_Terminate();
}
} // namespace hx::sound

#define HX_CREATE_SOUND_CONTEXT()           \
    hx::sound::Context x_portaudio_context; \
    static_cast<void>(x_portaudio_context)
