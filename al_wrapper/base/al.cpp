#pragma once

#include "al.hpp"

namespace al_wrapper
{
    void set_doppler_factor(ALfloat value) { alDopplerFactor(value); }
    void set_doppler_velocity(ALfloat value) { alDopplerVelocity(value); }
    void set_speed_of_sound(ALfloat value) { alSpeedOfSound(value); }
    void set_distance_model(DistanceModel model) { alDistanceModel(static_cast<ALenum>(model)); }

    std::string get_string(ALenum param) { return alGetString(param); }
    void get_booleanv(ALenum param, ALboolean *values) { alGetBooleanv(param, values); }
    void get_integerv(ALenum param, ALint *values) { alGetIntegerv(param, values); }
    void get_floatv(ALenum param, ALfloat *values) { alGetFloatv(param, values); }
    void get_doublev(ALenum param, ALdouble *values) { alGetDoublev(param, values); }
    ALboolean get_boolean(ALenum param) { return alGetBoolean(param); }
    ALint get_integer(ALenum param) { return alGetInteger(param); }
    ALfloat get_float(ALenum param) { return alGetFloat(param); }
    ALdouble get_double(ALenum param) { return alGetDouble(param); }

    ALError get_error() { return static_cast<ALError>(alGetError()); }
    ALboolean is_extension_present(const std::string &extname) { return alIsExtensionPresent(extname.data()); }
    void *get_proc_address(const std::string &fname) { return alGetProcAddress(fname.data()); }
    ALenum get_enum_value(const std::string &ename) { return alGetEnumValue(ename.data()); }

} // namespace al_wrapper
