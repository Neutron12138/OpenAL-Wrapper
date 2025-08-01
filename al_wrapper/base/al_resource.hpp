#pragma once

#include <base/misc/resource.hpp>
#include "al.hpp"

namespace al_wrapper
{
    BASE_DECLARE_REF_TYPE(ALResource);

    /// @brief OpenAL资源基类
    class ALResource : public base::Resource
    {
    public:
        /// @brief 资源类型
        enum class ResourceType : base::Int64
        {
            /// @brief 无
            None,
            /// @brief 缓冲区
            Buffer,
            /// @brief 声源
            Source,
        };

    protected:
        /// @brief 资源ID
        ALuint m_id = 0;

    public:
        ALResource() = default;
        ALResource(ALResource &&from);
        ~ALResource() override = default;
        BASE_DELETE_COPY_FUNCTION(ALResource);

    public:
        virtual ALResource &operator=(ALResource &&from);
        operator ALuint() const;
        ALuint get_id() const;
        bool is_valid() const override;
    };

} // namespace al_wrapper
