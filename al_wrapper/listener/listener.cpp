#pragma once

#include "listener.hpp"

namespace al_wrapper
{
    Listener &Listener::get_instance()
    {
        static Listener instance;
        return instance;
    }

    void Listener::set_parameter(ParameterName param, ALint value)
    {
        alListeneri(static_cast<ALenum>(param), value);
    }

    void Listener::set_parameter(ParameterName param, ALfloat value)
    {
        alListenerf(static_cast<ALenum>(param), value);
    }

    void Listener::set_parameter(ParameterName param, const glm::ivec3 &value)
    {
        alListeneriv(static_cast<ALenum>(param), glm::value_ptr(value));
    }

    void Listener::set_parameter(ParameterName param, const glm::vec3 &value)
    {
        alListenerfv(static_cast<ALenum>(param), glm::value_ptr(value));
    }

    void Listener::set_parameter(ParameterName param, const Orientation &orientation)
    {
        alListenerfv(static_cast<ALenum>(param), orientation);
    }

    void Listener::get_parameter(ParameterName param, ALint &result) const
    {
        alGetListeneri(static_cast<ALenum>(param), &result);
    }

    void Listener::get_parameter(ParameterName param, ALfloat &result) const
    {
        alGetListenerf(static_cast<ALenum>(param), &result);
    }

    void Listener::get_parameter(ParameterName param, glm::ivec3 &result) const
    {
        alGetListeneriv(static_cast<ALenum>(param), glm::value_ptr(result));
    }

    void Listener::get_parameter(ParameterName param, glm::vec3 &result) const
    {
        alGetListenerfv(static_cast<ALenum>(param), glm::value_ptr(result));
    }

    void Listener::get_parameter(ParameterName param, Orientation &result) const
    {
        alGetListenerfv(static_cast<ALenum>(param), result);
    }

    void Listener::set_gain(ALfloat value) { set_parameter(ParameterName::Gain, value); }
    void Listener::set_position(const glm::vec3 &position) { set_parameter(ParameterName::Position, position); }
    void Listener::set_velocity(const glm::vec3 &velocity) { set_parameter(ParameterName::Velocity, velocity); }
    void Listener::set_orientation(const Orientation &orientation) { set_parameter(ParameterName::Orientation, orientation); }

    ALfloat Listener::get_gain() const { return get_parameter<ALfloat>(ParameterName::Gain); }
    glm::vec3 Listener::get_position() const { return get_parameter<glm::vec3>(ParameterName::Position); }
    glm::vec3 Listener::get_velocity() const { return get_parameter<glm::vec3>(ParameterName::Velocity); }
    Orientation Listener::get_orientation() const { return get_parameter<Orientation>(ParameterName::Orientation); }

} // namespace al_wrapper
