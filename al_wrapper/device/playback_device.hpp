#pragma once

#include "device.hpp"

namespace al_wrapper
{
    BASE_DECLARE_REF_TYPE(PlaybackDevice);
    class PlaybackContext;

    /// @brief 播放设备
    class PlaybackDevice : public Device
    {
    public:
        PlaybackDevice() = default;
        PlaybackDevice(PlaybackDevice &&from);
        ~PlaybackDevice() override;
        BASE_DELETE_COPY_FUNCTION(PlaybackDevice);

    public:
        PlaybackDevice &operator=(PlaybackDevice &&from);
        base::Int64 get_resource_type() const override;

    public:
        void create();
        void create(const std::string &devicename);
        void destroy();

    public:
        PlaybackContext create_context() const;
        PlaybackContext create_context(const std::vector<ALCint> &attrlist) const;
    };

    PlaybackDevice create_device();
    PlaybackDeviceRef create_device_shared();
    PlaybackDeviceUniqueRef create_device_unique();

    PlaybackDevice create_device(const std::string &devicename);
    PlaybackDeviceRef create_device_shared(const std::string &devicename);
    PlaybackDeviceUniqueRef create_device_unique(const std::string &devicename);

} // namespace al_wrapper
