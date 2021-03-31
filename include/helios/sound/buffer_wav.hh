/*
 * buffer_wav.hh
 * Created: 2021-03-31, 18:39:12.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <helios/fs.hh>
#include <helios/sound/buffer.hh>
#include <dr_wav.h>
#include <vector>

namespace hx::sound
{
class Buffer_WAV : public Buffer<Buffer_WAV> {
public:
    void clear();
    bool loadFromFile(const fs::path &path);

    int getChannelCount() const;
    double getSampleRate() const;
    const std::vector<float> &getSamples() const;

private:
    drwav_uint16 channels = 0;
    drwav_uint32 sample_rate = 0;
    std::vector<float> samples;
};

inline void Buffer_WAV::clear()
{
    channels = 0;
    sample_rate = 0;
    samples.clear();
}

inline bool Buffer_WAV::loadFromFile(const fs::path &path)
{
    clear();

    if(!fs::exists(path))
        return false;
    
    std::vector<uint8_t> data = fs::readBinaryFile(path);
    
    drwav wav;
    if(!drwav_init_memory(&wav, data.data(), data.size(), nullptr))
        return false;
    
    channels = wav.channels;
    sample_rate = wav.sampleRate;
    samples.resize(static_cast<size_t>(wav.totalPCMFrameCount) * wav.channels);
    drwav_read_pcm_frames_f32(&wav, wav.totalPCMFrameCount, samples.data());

    drwav_uninit(&wav);
    return true;
}

inline int Buffer_WAV::getChannelCount() const
{
    return static_cast<int>(channels);
}

inline double Buffer_WAV::getSampleRate() const
{
    return static_cast<double>(sample_rate);
}

inline const std::vector<float> &Buffer_WAV::getSamples() const
{
    return samples;
}
} // namespace hx::sound
