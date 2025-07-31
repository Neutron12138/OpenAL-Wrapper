#pragma once

#include <vector>
#include <array>
#include "../base/alc_resource.hpp"

namespace al_wrapper
{
    BASE_DECLARE_REF_TYPE(Context);
    class Device;

    /// @brief 上下文
    class Context : public ALCResource
    {
    public:
        static ALCcontext *get_current_context();

    private:
        /// @brief 上下文
        ALCcontext *m_context = nullptr;

    public:
        Context() = default;
        Context(Context &&from);
        ~Context() override;
        BASE_DELETE_COPY_FUNCTION(Context);

    public:
        Context &operator=(Context &&from);
        base::Int64 get_resource_type() const override;
        operator ALCcontext *() const;
        ALCcontext *get_context() const;
        bool is_valid() const override;

    public:
        ALCdevice *get_device() const;
        void make_context_current();
        void suspend();
        void process();

    public:
        void create(const Device &device);
        void create(const Device &device, const std::vector<ALCint> &attrlist);
        void destroy();

        template <std::size_t N>
        void create(const Device &device, const std::array<ALCint, N> &attrlist)
        {
            destroy();
            m_context = alcCreateContext(device, attrlist.data());
            if (!m_context)
                throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to create context, device: ", device.get_device());
        }
    };

    Context create_context_from_device(const Device &device);
    ContextRef create_context_shared_from_device(const Device &device);
    ContextUniqueRef create_context_unique_from_device(const Device &device);

    Context create_context_from_device(const Device &device, const std::vector<ALCint> &attrlist);
    ContextRef create_context_shared_from_device(const Device &device, const std::vector<ALCint> &attrlist);
    ContextUniqueRef create_context_unique_from_device(const Device &device, const std::vector<ALCint> &attrlist);

    template <std::size_t N>
    Context create_context_from_device(const Device &device, const std::array<ALCint, N> &attrlist)
    {
        Context context;
        context.create(device, attrlist);
        return context;
    }

    template <std::size_t N>
    ContextRef create_context_shared_from_device(const Device &device, const std::array<ALCint, N> &attrlist)
    {
        ContextRef context = std::make_shared<Context>();
        context->create(device, attrlist);
        return context;
    }

    template <std::size_t N>
    ContextUniqueRef create_context_unique_from_device(const Device &device, const std::array<ALCint, N> &attrlist)
    {
        ContextUniqueRef context = std::make_unique<Context>();
        context->create(device, attrlist);
        return context;
    }

} // namespace al_wrapper
