#pragma once

#include "capture_device.hpp"

namespace al_wrapper
{
    CaptureDevice::CaptureDevice(CaptureDevice &&from)
        : Device(std::move(from)) {}

    CaptureDevice::~CaptureDevice() { destroy(); }

    CaptureDevice &CaptureDevice::operator=(CaptureDevice &&from)
    {
        destroy();
        m_device = std::exchange(from.m_device, nullptr);
        return *this;
    }

    base::Int64 CaptureDevice::get_resource_type() const { return static_cast<base::Int64>(ResourceType::CaptureDevice); }

    void CaptureDevice::create(ALCuint frequency, Format format, ALCsizei buffersize)
    {
        destroy();
        m_device = alcCaptureOpenDevice(nullptr, frequency, static_cast<ALenum>(format), buffersize);
        if (!m_device)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR(
                "Failed to open default capture device\n",
                "frequency: ", frequency,
                ", format: ", static_cast<ALenum>(format),
                ", buffer size: ", buffersize);
    }

    void CaptureDevice::create(const std::string &devicename, ALCuint frequency, Format format, ALCsizei buffersize)
    {
        destroy();
        m_device = alcCaptureOpenDevice(devicename.data(), frequency, static_cast<ALenum>(format), buffersize);
        if (!m_device)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR(
                "Failed to open default capture device\n",
                "device name: \"", devicename,
                "\", frequency: ", frequency,
                ", format: ", static_cast<ALenum>(format),
                ", buffer size: ", buffersize);
    }

    void CaptureDevice::destroy()
    {
        if (!m_device)
            return;

        alcCaptureCloseDevice(m_device);
        m_device = nullptr;
    }

    void CaptureDevice::start() { alcCaptureStart(m_device); }
    void CaptureDevice::stop() { alcCaptureStop(m_device); }
    void CaptureDevice::read_samples(ALCvoid *buffer, ALCsizei samples) { alcCaptureSamples(m_device, buffer, samples); }

    void CaptureDevice::read_samples(std::vector<base::Int8> &buffer)
    {
        read_samples(buffer.data(), buffer.size());
    }

    void CaptureDevice::read_samples(std::vector<base::Int16> &buffer)
    {
        read_samples(buffer.data(), buffer.size());
    }

    CaptureDevice create_capture_device(ALCuint frequency, Format format, ALCsizei buffersize)
    {
        CaptureDevice device;
        device.create(frequency, format, buffersize);
        return device;
    }

    CaptureDeviceRef create_capture_device_shared(ALCuint frequency, Format format, ALCsizei buffersize)
    {
        CaptureDeviceRef device = std::make_shared<CaptureDevice>();
        device->create(frequency, format, buffersize);
        return device;
    }

    CaptureDeviceUniqueRef create_capture_device_unique(ALCuint frequency, Format format, ALCsizei buffersize)
    {
        CaptureDeviceUniqueRef device = std::make_unique<CaptureDevice>();
        device->create(frequency, format, buffersize);
        return device;
    }

    CaptureDevice create_capture_device(const std::string &devicename, ALCuint frequency,
                                        Format format, ALCsizei buffersize)
    {
        CaptureDevice device;
        device.create(devicename, frequency, format, buffersize);
        return device;
    }

    CaptureDeviceRef create_capture_device_shared(const std::string &devicename, ALCuint frequency,
                                                  Format format, ALCsizei buffersize)
    {
        CaptureDeviceRef device = std::make_shared<CaptureDevice>();
        device->create(devicename, frequency, format, buffersize);
        return device;
    }

    CaptureDeviceUniqueRef create_capture_device_unique(const std::string &devicename, ALCuint frequency,
                                                        Format format, ALCsizei buffersize)
    {
        CaptureDeviceUniqueRef device = std::make_unique<CaptureDevice>();
        device->create(devicename, frequency, format, buffersize);
        return device;
    }

} // namespace al_wrapper
