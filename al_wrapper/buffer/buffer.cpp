#pragma once

#include "buffer.hpp"

namespace al_wrapper
{
    Buffer::Buffer(Buffer &&from)
        : ALResource(std::move(from)) {}

    Buffer::~Buffer() { destroy(); }

    Buffer &Buffer::operator=(Buffer &&from)
    {
        destroy();
        m_id = std::exchange(from.m_id, 0);
        return *this;
    }

    base::Int64 Buffer::get_resource_type() const { return static_cast<base::Int64>(ResourceType::Buffer); }

    void Buffer::create()
    {
        destroy();
        alGenBuffers(1, &m_id);
        if (m_id == 0)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to create Buffer object");
    }

    void Buffer::destroy()
    {
        if (m_id == 0)
            return;

        alDeleteBuffers(1, &m_id);
        m_id = 0;
    }

    void Buffer::set_data(Format format, const ALvoid *data, ALsizei size, ALsizei samplerate)
    {
        alBufferData(m_id, static_cast<ALenum>(format), data, size, samplerate);
    }

    void Buffer::set_mono_data(const std::vector<base::Int8> &data, ALsizei samplerate)
    {
        set_data(Format::Mono8, data, samplerate);
    }

    void Buffer::set_mono_data(const std::vector<base::Int16> &data, ALsizei samplerate)
    {
        set_data(Format::Mono16, data, samplerate);
    }

    void Buffer::set_stereo_data(const std::vector<base::Int8> &data, ALsizei samplerate)
    {
        set_data(Format::Stereo8, data, samplerate);
    }

    void Buffer::set_stereo_data(const std::vector<base::Int16> &data, ALsizei samplerate)
    {
        set_data(Format::Stereo16, data, samplerate);
    }

    void Buffer::set_parameter(ParameterName param, ALint value)
    {
        alBufferi(m_id, static_cast<ALenum>(param), value);
    }

    void Buffer::get_parameter(ParameterName param, ALint &result) const
    {
        alGetBufferi(m_id, static_cast<ALenum>(param), &result);
    }

    Buffer create_buffer()
    {
        Buffer buffer;
        buffer.create();
        return buffer;
    }

    BufferRef create_buffer_shared()
    {
        BufferRef buffer = std::make_shared<Buffer>();
        buffer->create();
        return buffer;
    }

    BufferUniqueRef create_buffer_unique()
    {
        BufferUniqueRef buffer = std::make_unique<Buffer>();
        buffer->create();
        return buffer;
    }

    Buffer create_buffer_from_mono_data(const std::vector<base::Int8> &data, ALsizei samplerate)
    {
        Buffer buffer = create_buffer();
        buffer.set_mono_data(data, samplerate);
        return buffer;
    }

    Buffer create_buffer_from_mono_data(const std::vector<base::Int16> &data, ALsizei samplerate)
    {
        Buffer buffer = create_buffer();
        buffer.set_mono_data(data, samplerate);
        return buffer;
    }

    Buffer create_buffer_from_stereo_data(const std::vector<base::Int8> &data, ALsizei samplerate)
    {
        Buffer buffer = create_buffer();
        buffer.set_stereo_data(data, samplerate);
        return buffer;
    }

    Buffer create_buffer_from_stereo_data(const std::vector<base::Int16> &data, ALsizei samplerate)
    {
        Buffer buffer = create_buffer();
        buffer.set_stereo_data(data, samplerate);
        return buffer;
    }

} // namespace al_wrapper
