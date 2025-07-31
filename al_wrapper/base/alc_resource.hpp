#pragma once

#include <AL/alc.h>
#include <base/misc/resource.hpp>

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
            /// @brief 设备
            Device,
            /// @brief 上下文
            Context,
        };

    public:
        ALCResource() = default;
        ~ALCResource() override = default;
        BASE_DELETE_COPY_FUNCTION(ALCResource);
    };

} // namespace al_wrapper
