#pragma once

#include "source.hpp"
#include "../buffer/buffer.hpp"

namespace al_wrapper
{
    Source::Source(Source &&from)
        : ALResource(std::move(from)) {}

    Source::~Source() { destroy(); }

    Source &Source::operator=(Source &&from)
    {
        destroy();
        m_id = std::exchange(from.m_id, 0);
        return *this;
    }

    base::Int64 Source::get_resource_type() const { return static_cast<base::Int64>(ResourceType::Source); }

    void Source::create()
    {
        destroy();
        alGenSources(1, &m_id);
        if (m_id == 0)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to create Source object");
    }

    void Source::destroy()
    {
        if (m_id == 0)
            return;

        alDeleteSources(1, &m_id);
        m_id = 0;
    }

    void Source::play() { alSourcePlay(m_id); }
    void Source::stop() { alSourceStop(m_id); }
    void Source::rewind() { alSourceRewind(m_id); }
    void Source::pause() { alSourcePause(m_id); }

    void Source::set_buffer() { alSourcei(m_id, AL_BUFFER, AL_NONE); }
    void Source::set_buffer(const Buffer &buffer) { alSourcei(m_id, AL_BUFFER, buffer); }
    Source::State Source::get_state() const { return static_cast<State>(get_parameter<ALint>(ParameterName::SourceState)); }

    void Source::set_parameter(ParameterName param, ALint value)
    {
        alSourcei(m_id, static_cast<ALenum>(param), value);
    }

    void Source::set_parameter(ParameterName param, ALfloat value)
    {
        alSourcef(m_id, static_cast<ALenum>(param), value);
    }

    void Source::set_parameter(ParameterName param, const glm::ivec3 &value)
    {
        alSourceiv(m_id, static_cast<ALenum>(param), glm::value_ptr(value));
    }

    void Source::set_parameter(ParameterName param, const glm::vec3 &value)
    {
        alSourcefv(m_id, static_cast<ALenum>(param), glm::value_ptr(value));
    }

    void Source::get_parameter(ParameterName param, ALint &result) const
    {
        alGetSourcei(m_id, static_cast<ALenum>(param), &result);
    }

    void Source::get_parameter(ParameterName param, ALfloat &result) const
    {
        alGetSourcef(m_id, static_cast<ALenum>(param), &result);
    }

    void Source::get_parameter(ParameterName param, glm::ivec3 &value) const
    {
        alGetSourceiv(m_id, static_cast<ALenum>(param), glm::value_ptr(value));
    }

    void Source::get_parameter(ParameterName param, glm::vec3 &value) const
    {
        alGetSourcefv(m_id, static_cast<ALenum>(param), glm::value_ptr(value));
    }

    Source create_source()
    {
        Source source;
        source.create();
        return source;
    }

    SourceRef create_source_shared()
    {
        SourceRef source = std::make_shared<Source>();
        source->create();
        return source;
    }

    SourceUniqueRef create_source_unique()
    {
        SourceUniqueRef source = std::make_unique<Source>();
        source->create();
        return source;
    }

} // namespace al_wrapper
