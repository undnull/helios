/*
 * out_stream.cc
 * Created: 2021-03-31, 19:02:41.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#include <helios/sound/out_stream.hh>

namespace hx::sound
{
int OutStream::paCallback(const void *in, void *out, unsigned long frames, const PaStreamCallbackTimeInfo *time, PaStreamCallbackFlags flags, void *data)
{
    OutStream *me = reinterpret_cast<OutStream *>(data);
    float *f_out = reinterpret_cast<float *>(out);
    for(unsigned long i = 0; i < frames; i++) {
        for(int j = 0; j < me->num_channels; j++) {
            if(me->cur_sample >= me->samples.size()) {
                if(!me->loop)
                    return paComplete;
                me->cur_sample = 0;
            }
            *f_out++ = me->samples[me->cur_sample++] * me->volume;
        }
    }
    return paContinue;
}

void OutStream::paFinish(void *data)
{
    OutStream *me = reinterpret_cast<OutStream *>(data);
    me->status = Status::Stopped; 
}
} // namespace hx::sound
