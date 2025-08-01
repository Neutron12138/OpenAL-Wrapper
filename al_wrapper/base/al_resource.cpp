#pragma once

#include "al_resource.hpp"

namespace al_wrapper
{
    ALResource::ALResource(ALResource &&from)
        : m_id(std::exchange(from.m_id, 0)) {}

    ALResource &ALResource::operator=(ALResource &&from)
    {
        m_id = std::exchange(from.m_id, 0);
        return *this;
    }

    ALResource::operator ALuint() const { return m_id; }
    ALuint ALResource::get_id() const { return m_id; }
    bool ALResource::is_valid() const { return m_id; }

} // namespace al_wrapper
