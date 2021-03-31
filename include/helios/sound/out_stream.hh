/*
 * out_stream.hh
 * Created: 2021-03-31, 18:51:47.
 * Copyright (C) 2021, Kirill GPRB.
 * 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */
#pragma once
#include <helios/sound/buffer.hh>
#include <portaudio.h>
#include <string.h>

namespace hx::sound
{
/**
 * @brief Output sound stream.
 * 
 */
class OutStream {
public:
    /**
     * @brief Playback status.
     * 
     */
    enum class Status {
        Init,
        Stopped,
        Playing,
        Paused
    };

public:
    /**
     * @brief Constructor.
     * 
     */
    OutStream();

    /**
     * @brief Destructor.
     * 
     */
    virtual ~OutStream();

    /**
     * @brief Initializes the stream with a sound buffer.
     * 
     * @param buffer Sound buffer.
     */
    template<typename T>
    void init(const Buffer<T> &buffer);

    /**
     * @brief Starts the playback.
     * 
     */
    void play();

    /**
     * @brief Pauses the playback.
     * 
     */
    void pause();

    /**
     * @brief Stops the playback.
     * 
     */
    void stop();

    /**
     * @brief Sets the playback volume.
     * 
     * @param volume Playback volume [0.0; 1.0]
     */
    void setVolume(float volume);

    /**
     * @brief Sets the loop flag.
     * 
     * @param loop Loop flag.
     */
    void setLoop(bool loop);

    /**
     * @brief Gets the playback status.
     * 
     * @return Playback status.
     */
    Status getStatus() const;

private:
    static int paCallback(const void *in, void *out, unsigned long frames, const PaStreamCallbackTimeInfo *time, PaStreamCallbackFlags flags, void *data);
    static void paFinish(void *data);

private:
    PaStream *stream;
    size_t cur_sample;
    int num_channels;
    std::vector<float> samples;
    Status status;
    float volume;
    bool loop;
};

inline OutStream::OutStream() : samples()
{
    stream = nullptr;
    num_channels = 0;
    cur_sample = 0;
    status = Status::Init;
    volume = 1.0f;
    loop = false;
}

inline OutStream::~OutStream()
{
    samples.clear();
    Pa_CloseStream(stream);
}

template<typename T>
inline void OutStream::init(const Buffer<T> &buffer)
{
    samples.clear();
    Pa_CloseStream(stream);

    num_channels = buffer.getChannelCount();
    samples = buffer.getSamples();
    cur_sample = 0;

    Pa_OpenDefaultStream(&stream, 0, num_channels, paFloat32, buffer.getSampleRate(), paFramesPerBufferUnspecified, paCallback, this);
    Pa_SetStreamFinishedCallback(stream, paFinish);
}

inline void OutStream::play()
{
    if(status != Status::Playing) {
        Pa_StartStream(stream);
        status = Status::Playing;
    }
}

inline void OutStream::pause()
{
    if(status == Status::Playing) {
        Pa_AbortStream(stream);
        status = Status::Paused;
    }
}

inline void OutStream::stop()
{
    if(status == Status::Playing) {
        Pa_AbortStream(stream);
        status = Status::Stopped;
        cur_sample = 0;
    }
}

inline void OutStream::setVolume(float volume)
{
    this->volume = volume;
}

inline void OutStream::setLoop(bool loop)
{
    this->loop = loop;
}

inline OutStream::Status OutStream::getStatus() const
{
    return status;
}
} // namespace hx::sound
