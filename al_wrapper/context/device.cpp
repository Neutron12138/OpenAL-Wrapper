#pragma once

#include "device.hpp"
#include "context.hpp"

namespace al_wrapper
{
    Device::Device(Device &&from)
        : m_device(std::exchange(from.m_device, nullptr)) {}

    Device::~Device() { destroy(); }

    Device &Device::operator=(Device &&from)
    {
        destroy();
        m_device = std::exchange(from.m_device, nullptr);
        return *this;
    }

    base::Int64 Device::get_resource_type() const { return static_cast<base::Int64>(ResourceType::Device); }
    Device::operator ALCdevice *() const { return m_device; }
    ALCdevice *Device::get_device() const { return m_device; }
    bool Device::is_valid() const { return m_device; }

    void Device::create()
    {
        destroy();
        m_device = alcOpenDevice(nullptr);
        if (!m_device)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to open default playback device");
    }

    void Device::create(const std::string &devicename)
    {
        destroy();
        m_device = alcOpenDevice(devicename.data());
        if (!m_device)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to open playback device, name: \"", devicename, "\"");
    }

    void Device::destroy()
    {
        if (!m_device)
            return;

        alcCloseDevice(m_device);
        m_device = nullptr;
    }

    Context Device::create_context() const { return create_context_from_device(*this); }
    Context Device::create_context(const std::vector<ALCint> &attrlist) const { return create_context_from_device(*this, attrlist); }

    Device create_device()
    {
        Device device;
        device.create();
        return device;
    }

    DeviceRef create_device_shared()
    {
        DeviceRef device = std::make_shared<Device>();
        device->create();
        return device;
    }

    DeviceUniqueRef create_device_unique()
    {
        DeviceUniqueRef device = std::make_unique<Device>();
        device->create();
        return device;
    }

    Device create_device(const std::string &devicename)
    {
        Device device;
        device.create(devicename);
        return device;
    }

    DeviceRef create_device_shared(const std::string &devicename)
    {
        DeviceRef device = std::make_shared<Device>();
        device->create(devicename);
        return device;
    }

    DeviceUniqueRef create_device_unique(const std::string &devicename)
    {
        DeviceUniqueRef device = std::make_unique<Device>();
        device->create(devicename);
        return device;
    }

} // namespace al_wrapper
