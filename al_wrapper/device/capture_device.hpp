#pragma once

#include <vector>
#include "device.hpp"
#include "../base/enums.hpp"

namespace al_wrapper
{
    BASE_DECLARE_REF_TYPE(CaptureDevice);

    /// @brief 捕获设备
    class CaptureDevice : public Device
    {
    public:
        CaptureDevice() = default;
        CaptureDevice(CaptureDevice &&from);
        ~CaptureDevice() override;
        BASE_DELETE_COPY_FUNCTION(CaptureDevice);

    public:
        CaptureDevice &operator=(CaptureDevice &&from);
        base::Int64 get_resource_type() const override;

    public:
        void create(ALCuint frequency, Format format, ALCsizei buffersize);
        void create(const std::string &devicename, ALCuint frequency, Format format, ALCsizei buffersize);
        void destroy();

    public:
        void start();
        void stop();
        void read_samples(ALCvoid *buffer, ALCsizei samples);
        void read_samples(std::vector<base::Int8> &buffer);
        void read_samples(std::vector<base::Int16> &buffer);
    };

    CaptureDevice create_capture_device(ALCuint frequency, Format format, ALCsizei buffersize);
    CaptureDeviceRef create_capture_device_shared(ALCuint frequency, Format format, ALCsizei buffersize);
    CaptureDeviceUniqueRef create_capture_device_unique(ALCuint frequency, Format format, ALCsizei buffersize);

    CaptureDevice create_capture_device(const std::string &devicename, ALCuint frequency,
                                        Format format, ALCsizei buffersize);
    CaptureDeviceRef create_capture_device_shared(const std::string &devicename, ALCuint frequency,
                                                  Format format, ALCsizei buffersize);
    CaptureDeviceUniqueRef create_capture_device_unique(const std::string &devicename, ALCuint frequency,
                                                        Format format, ALCsizei buffersize);

} // namespace al_wrapper
