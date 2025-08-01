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

    /// @brief OpenAL错误枚举
    enum class ALError : ALenum
    {
        NoError = AL_NO_ERROR,
        InvalidName = AL_INVALID_NAME,
        InvalidEnum = AL_INVALID_ENUM,
        InvalidValue = AL_INVALID_VALUE,
        InvalidOperation = AL_INVALID_OPERATION,
        OutOfMemory = AL_OUT_OF_MEMORY,
    };

    std::string get_string(ALenum param);
    void get_booleanv(ALenum param, ALboolean *values);
    void get_integerv(ALenum param, ALint *values);
    void get_floatv(ALenum param, ALfloat *values);
    void get_doublev(ALenum param, ALdouble *values);
    ALboolean get_boolean(ALenum param);
    ALint get_integer(ALenum param);
    ALfloat get_float(ALenum param);
    ALdouble get_double(ALenum param);

    ALError get_error();
    ALboolean is_extension_present(const std::string &extname);
    void *get_proc_address(const std::string &fname);
    ALenum get_enum_value(const std::string &ename);

} // namespace al_wrapper
