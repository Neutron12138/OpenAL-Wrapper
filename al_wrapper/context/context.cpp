#pragma once

#include "context.hpp"
#include "device.hpp"

namespace al_wrapper
{
    ALCcontext *Context::get_current_context() { return alcGetCurrentContext(); }

    Context::Context(Context &&from)
        : m_context(std::exchange(from.m_context, nullptr)) {}

    Context::~Context() { destroy(); }

    Context &Context::operator=(Context &&from)
    {
        destroy();
        m_context = std::exchange(from.m_context, nullptr);
        return *this;
    }

    base::Int64 Context::get_resource_type() const { return static_cast<base::Int64>(ResourceType::Context); }
    Context::operator ALCcontext *() const { return m_context; }
    ALCcontext *Context::get_context() const { return m_context; }
    bool Context::is_valid() const { return m_context; }

    ALCdevice *Context::get_device() const { return alcGetContextsDevice(m_context); }
    void Context::make_context_current() { alcMakeContextCurrent(m_context); }
    void Context::suspend() { alcSuspendContext(m_context); }
    void Context::process() { alcProcessContext(m_context); }

    void Context::create(const Device &device)
    {
        destroy();
        m_context = alcCreateContext(device, nullptr);
        if (!m_context)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to create context, device: ", device.get_device());
    }

    void Context::create(const Device &device, const std::vector<ALCint> &attrlist)
    {
        destroy();
        m_context = alcCreateContext(device, attrlist.data());
        if (!m_context)
            throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to create context, device: ", device.get_device());
    }

    void Context::destroy()
    {
        if (!m_context)
            return;

        alcDestroyContext(m_context);
        m_context = nullptr;
    }

    Context create_context_from_device(const Device &device)
    {
        Context context;
        context.create(device);
        return context;
    }

    ContextRef create_context_shared_from_device(const Device &device)
    {
        ContextRef context = std::make_shared<Context>();
        context->create(device);
        return context;
    }

    ContextUniqueRef create_context_unique_from_device(const Device &device)
    {
        ContextUniqueRef context = std::make_unique<Context>();
        context->create(device);
        return context;
    }

    Context create_context_from_device(const Device &device, const std::vector<ALCint> &attrlist)
    {
        Context context;
        context.create(device, attrlist);
        return context;
    }

    ContextRef create_context_shared_from_device(const Device &device, const std::vector<ALCint> &attrlist)
    {
        ContextRef context = std::make_shared<Context>();
        context->create(device, attrlist);
        return context;
    }

    ContextUniqueRef create_context_unique_from_device(const Device &device, const std::vector<ALCint> &attrlist)
    {
        ContextUniqueRef context = std::make_unique<Context>();
        context->create(device, attrlist);
        return context;
    }

} // namespace al_wrapper
