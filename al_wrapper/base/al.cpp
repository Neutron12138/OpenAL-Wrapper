#pragma once

#include "al.hpp"

namespace al_wrapper
{
    void set_doppler_factor(ALfloat value)
    {
        alDopplerFactor(value);
    }

    void set_doppler_velocity(ALfloat value)
    {
        alDopplerVelocity(value);
    }

    void set_speed_of_sound(ALfloat value)
    {
        alSpeedOfSound(value);
    }

    void set_distance_model(DistanceModel model)
    {
        alDistanceModel(static_cast<ALenum>(model));
    }

} // namespace al_wrapper
