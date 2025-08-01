#pragma once

#include "playback_device.hpp"
#include "../context/playback_context.hpp"

namespace al_wrapper
{
    PlaybackDevice::PlaybackDevice(PlaybackDevice &&from)
        : Device(std::move(from)) {}

    PlaybackDevice::~PlaybackDevice() { destroy(); }

    PlaybackDevice &PlaybackDevice::operator=(PlaybackDevice &&from)
    {
        destroy();
        m_device = std::exchange(from.m_device, nullptr);
        return *this;
    }

    base::Int64 PlaybackDevice::get_resource_type() const { return static_cast<base::Int64>(ResourceType::PlaybackDevice); }

    void PlaybackDevice::create()
    {
        destroy();
        m_device = alcOpenDevice(nullptr);
        if (!m_device)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to open default playback device");
    }

    void PlaybackDevice::create(const std::string &devicename)
    {
        destroy();
        m_device = alcOpenDevice(devicename.data());
        if (!m_device)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to open playback device, name: \"", devicename, "\"");
    }

    void PlaybackDevice::destroy()
    {
        if (!m_device)
            return;

        alcCloseDevice(m_device);
        m_device = nullptr;
    }

    PlaybackContext PlaybackDevice::create_context() const { return create_context_from_device(*this); }
    PlaybackContext PlaybackDevice::create_context(const std::vector<ALCint> &attrlist) const { return create_context_from_device(*this, attrlist); }

    PlaybackDevice create_device()
    {
        PlaybackDevice device;
        device.create();
        return device;
    }

    PlaybackDeviceRef create_device_shared()
    {
        PlaybackDeviceRef device = std::make_shared<PlaybackDevice>();
        device->create();
        return device;
    }

    PlaybackDeviceUniqueRef create_device_unique()
    {
        PlaybackDeviceUniqueRef device = std::make_unique<PlaybackDevice>();
        device->create();
        return device;
    }

    PlaybackDevice create_device(const std::string &devicename)
    {
        PlaybackDevice device;
        device.create(devicename);
        return device;
    }

    PlaybackDeviceRef create_device_shared(const std::string &devicename)
    {
        PlaybackDeviceRef device = std::make_shared<PlaybackDevice>();
        device->create(devicename);
        return device;
    }

    PlaybackDeviceUniqueRef create_device_unique(const std::string &devicename)
    {
        PlaybackDeviceUniqueRef device = std::make_unique<PlaybackDevice>();
        device->create(devicename);
        return device;
    }

} // namespace al_wrapper
