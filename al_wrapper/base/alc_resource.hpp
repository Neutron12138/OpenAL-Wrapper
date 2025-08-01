#pragma once

#include <base/misc/resource.hpp>
#include "alc.hpp"

namespace al_wrapper
{
    BASE_DECLARE_REF_TYPE(ALCResource);

    /// @brief OpenAL上下文资源
    class ALCResource : public base::Resource
    {
    public:
        /// @brief 资源类型
        enum class ResourceType : base::Int64
        {
            /// @brief 无
            None,
            /// @brief 播放设备
            PlaybackDevice,
            /// @brief 播放上下文
            PlaybackContext,
            /// @brief 捕获设备
            CaptureDevice,
        };

    public:
        ALCResource() = default;
        ~ALCResource() override = default;
        BASE_DELETE_COPY_FUNCTION(ALCResource);
    };

} // namespace al_wrapper
