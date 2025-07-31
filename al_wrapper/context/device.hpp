#pragma once

#include "../base/alc_resource.hpp"

namespace al_wrapper
{
    BASE_DECLARE_REF_TYPE(Device);
    class Context;

    /// @brief 设备
    class Device : public ALCResource
    {
    private:
        /// @brief 设备
        ALCdevice *m_device = nullptr;

    public:
        Device() = default;
        Device(Device &&from);
        ~Device() override;
        BASE_DELETE_COPY_FUNCTION(Device);

    public:
        Device &operator=(Device &&from);
        base::Int64 get_resource_type() const override;
        operator ALCdevice *() const;
        ALCdevice *get_device() const;
        bool is_valid() const override;

    public:
        void create();
        void create(const std::string &devicename);
        void destroy();

    public:
        Context create_context() const;
        Context create_context(const std::vector<ALCint> &attrlist) const;
    };

    Device create_device();
    DeviceRef create_device_shared();
    DeviceUniqueRef create_device_unique();

    Device create_device(const std::string &devicename);
    DeviceRef create_device_shared(const std::string &devicename);
    DeviceUniqueRef create_device_unique(const std::string &devicename);

} // namespace al_wrapper
