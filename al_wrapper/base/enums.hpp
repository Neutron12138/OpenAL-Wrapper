#pragma once

#include "al.hpp"

namespace al_wrapper
{
    /// @brief 格式
    enum class Format : ALenum
    {
        Mono8 = AL_FORMAT_MONO8,
        Mono16 = AL_FORMAT_MONO16,
        Stereo8 = AL_FORMAT_STEREO8,
        Stereo16 = AL_FORMAT_STEREO16,
    };
    
} // namespace al_wrapper

