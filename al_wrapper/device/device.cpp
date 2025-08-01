#pragma once

#include "device.hpp"

namespace al_wrapper
{
    Device::Device(Device &&from)
        : m_device(std::exchange(from.m_device, nullptr)) {}

    Device &Device::operator=(Device &&from)
    {
        m_device = std::exchange(from.m_device, nullptr);
        return *this;
    }

    Device::operator ALCdevice *() const { return m_device; }
    ALCdevice *Device::get_device() const { return m_device; }
    bool Device::is_valid() const { return m_device; }

    ALCError Device::get_error() const { return static_cast<ALCError>(alcGetError(m_device)); }
    ALCboolean Device::is_extension_present(const std::string &extname) const { return alcIsExtensionPresent(m_device, extname.data()); }
    ALCvoid *Device::get_proc_address(const std::string &funcname) const { return alcGetProcAddress(m_device, funcname.data()); }
    ALCenum Device::get_enum_value(const std::string &enumname) const { return alcGetEnumValue(m_device, enumname.data()); }
    std::string Device::get_string(ALCenum param) const { return alcGetString(m_device, param); }
    void Device::get_integerv(ALCenum param, ALCsizei size, ALCint *values) const { alcGetIntegerv(m_device, param, size, values); }

} // namespace al_wrapper
