/*
 * buffer_flac.hh
 * Created: 2021-03-31, 20:49:23.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <helios/fs.hh>
#include <helios/sound/buffer.hh>
#include <dr_flac.h>
#include <vector>

namespace hx::sound
{
/**
 * @brief A FLAC sound buffer.
 * 
 */
class Buffer_FLAC : public Buffer<Buffer_FLAC> {
public:
    /**
     * @brief Clears the buffer.
     * 
     */
    void clear();

    /**
     * @brief (Re-)loads the buffer from a file.
     * 
     * @param path File path.
     * @return true if succeeded, false otherwise.
     */
    bool loadFromFile(const fs::path &path);

    /**
     * @brief Gets the number of channels.
     * 
     * @return Number of channels.
     */
    int getChannelCount() const;

    /**
     * @brief Gets the sample rate.
     * 
     * @return Sample rate.
     */
    double getSampleRate() const;

    /**
     * @brief Gets the sample buffer.
     * 
     * @return Sample buffer. 
     */
    const std::vector<float> &getSamples() const;

private:
    drflac_uint8 channels = 0;
    drflac_uint32 sample_rate = 0;
    std::vector<float> samples;
};

inline void Buffer_FLAC::clear()
{
    channels = 0;
    sample_rate = 0;
    samples.clear();
}

inline bool Buffer_FLAC::loadFromFile(const fs::path &path)
{
    clear();

    if(!fs::exists(path))
        return false;
    
    std::vector<uint8_t> data = fs::readBinaryFile(path);
    
    drflac *flac = drflac_open_memory(data.data(), data.size(), nullptr);
    if(!flac)
        return false;
    
    channels = flac->channels;
    sample_rate = flac->sampleRate;
    samples.resize(static_cast<size_t>(flac->totalPCMFrameCount) * flac->channels);
    drflac_read_pcm_frames_f32(flac, flac->totalPCMFrameCount, samples.data());

    drflac_close(flac);
    return true;
}

inline int Buffer_FLAC::getChannelCount() const
{
    return static_cast<int>(channels);
}

inline double Buffer_FLAC::getSampleRate() const
{
    return static_cast<double>(sample_rate);
}

inline const std::vector<float> &Buffer_FLAC::getSamples() const
{
    return samples;
}
} // namespace hx::sound
