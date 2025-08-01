#pragma once

#include "playback_context.hpp"

namespace al_wrapper
{
    ALCcontext *PlaybackContext::get_current_context() { return alcGetCurrentContext(); }
    void PlaybackContext::clear_context_current() { alcMakeContextCurrent(nullptr); }

    PlaybackContext::PlaybackContext(PlaybackContext &&from)
        : m_context(std::exchange(from.m_context, nullptr)) {}

    PlaybackContext::~PlaybackContext() { destroy(); }

    PlaybackContext &PlaybackContext::operator=(PlaybackContext &&from)
    {
        destroy();
        m_context = std::exchange(from.m_context, nullptr);
        return *this;
    }

    base::Int64 PlaybackContext::get_resource_type() const { return static_cast<base::Int64>(ResourceType::PlaybackContext); }
    PlaybackContext::operator ALCcontext *() const { return m_context; }
    ALCcontext *PlaybackContext::get_context() const { return m_context; }
    bool PlaybackContext::is_valid() const { return m_context; }

    ALCdevice *PlaybackContext::get_device() const { return alcGetContextsDevice(m_context); }
    void PlaybackContext::make_context_current() { alcMakeContextCurrent(m_context); }
    void PlaybackContext::suspend() { alcSuspendContext(m_context); }
    void PlaybackContext::process() { alcProcessContext(m_context); }

    void PlaybackContext::create(const PlaybackDevice &device)
    {
        destroy();
        m_context = alcCreateContext(device, nullptr);
        if (!m_context)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to create context, device: ", device.get_device());
    }

    void PlaybackContext::create(const PlaybackDevice &device, const std::vector<ALCint> &attrlist)
    {
        destroy();
        m_context = alcCreateContext(device, attrlist.data());
        if (!m_context)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to create context, device: ", device.get_device());
    }

    void PlaybackContext::destroy()
    {
        if (!m_context)
            return;

        alcDestroyContext(m_context);
        m_context = nullptr;
    }

    PlaybackContext create_context_from_device(const PlaybackDevice &device)
    {
        PlaybackContext context;
        context.create(device);
        return context;
    }

    PlaybackContextRef create_context_shared_from_device(const PlaybackDevice &device)
    {
        PlaybackContextRef context = std::make_shared<PlaybackContext>();
        context->create(device);
        return context;
    }

    PlaybackContextUniqueRef create_context_unique_from_device(const PlaybackDevice &device)
    {
        PlaybackContextUniqueRef context = std::make_unique<PlaybackContext>();
        context->create(device);
        return context;
    }

    PlaybackContext create_context_from_device(const PlaybackDevice &device, const std::vector<ALCint> &attrlist)
    {
        PlaybackContext context;
        context.create(device, attrlist);
        return context;
    }

} // namespace al_wrapper
