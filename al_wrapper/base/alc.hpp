#pragma once

#include <AL/alc.h>

namespace al_wrapper
{
    /// @brief OpenAL上下文错误枚举
    enum class ALCError : ALCenum
    {
        NoError = ALC_NO_ERROR,
        InvalidDevice = ALC_INVALID_DEVICE,
        InvalidContext = ALC_INVALID_CONTEXT,
        InvalidEnum = ALC_INVALID_ENUM,
        InvalidValue = ALC_INVALID_VALUE,
        OutOfMemory = ALC_OUT_OF_MEMORY,
    };

} // namespace al_wrapper
