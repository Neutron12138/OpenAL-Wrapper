#pragma once

#include <string>
#include <AL/al.h>

namespace al_wrapper
{
    /// @brief 距离模型
    enum class DistanceModel : ALenum
    {
        None = AL_NONE,
        InverseDistance = AL_INVERSE_DISTANCE,
        InverseDistanceClamped = AL_INVERSE_DISTANCE_CLAMPED,
        LinearDistance = AL_LINEAR_DISTANCE,
        LinearDistanceClamped = AL_LINEAR_DISTANCE_CLAMPED,
        ExponentDistance = AL_EXPONENT_DISTANCE,
        ExponentDistanceClamped = AL_EXPONENT_DISTANCE_CLAMPED,
    };

    void set_doppler_factor(ALfloat value);
    void set_doppler_velocity(ALfloat value);
    void set_speed_of_sound(ALfloat value);
    void set_distance_model(DistanceModel model = DistanceModel::InverseDistanceClamped);

} // namespace al_wrapper
