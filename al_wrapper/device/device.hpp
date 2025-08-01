#pragma once

#include <string>
#include "../base/alc_resource.hpp"

namespace al_wrapper
{
    BASE_DECLARE_REF_TYPE(Device);

    /// @brief 设备基类
    class Device : public ALCResource
    {
    protected:
        /// @brief 设备
        ALCdevice *m_device = nullptr;

    public:
        Device() = default;
        Device(Device &&from);
        ~Device() override = default;
        BASE_DELETE_COPY_FUNCTION(Device);

    public:
        Device &operator=(Device &&from);
        operator ALCdevice *() const;
        ALCdevice *get_device() const;
        bool is_valid() const override;

    public:
        ALCError get_error() const;
        ALCboolean is_extension_present(const std::string &extname) const;
        ALCvoid *get_proc_address(const std::string &funcname) const;
        ALCenum get_enum_value(const std::string &enumname) const;
        std::string get_string(ALCenum param) const;
        void get_integerv(ALCenum param, ALCsizei size, ALCint *values) const;
    };

} // namespace al_wrapper
