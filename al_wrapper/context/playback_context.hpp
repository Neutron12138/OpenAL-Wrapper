#pragma once

#include <vector>
#include <array>
#include "../base/alc_resource.hpp"
#include "../device/playback_device.hpp"

namespace al_wrapper
{
    BASE_DECLARE_REF_TYPE(PlaybackContext);
    class PlaybackDevice;

    /// @brief 播放上下文Playback
    class PlaybackContext : public ALCResource
    {
    public:
        static ALCcontext *get_current_context();
        static void clear_context_current();

    private:
        /// @brief 上下文
        ALCcontext *m_context = nullptr;

    public:
        PlaybackContext() = default;
        PlaybackContext(PlaybackContext &&from);
        ~PlaybackContext() override;
        BASE_DELETE_COPY_FUNCTION(PlaybackContext);

    public:
        PlaybackContext &operator=(PlaybackContext &&from);
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
        void create(const PlaybackDevice &device);
        void create(const PlaybackDevice &device, const std::vector<ALCint> &attrlist);
        void destroy();

        template <std::size_t N>
        void create(const PlaybackDevice &device, const std::array<ALCint, N> &attrlist)
        {
            destroy();
            m_context = alcCreateContext(device, attrlist.data());
            if (!m_context)
                throw BASE_MAKE_CLASS_RUNTIME_ERROR("Failed to create context, device: ", device.get_device());
        }
    };

    PlaybackContext create_context_from_device(const PlaybackDevice &device);
    PlaybackContextRef create_context_shared_from_device(const PlaybackDevice &device);
    PlaybackContextUniqueRef create_context_unique_from_device(const PlaybackDevice &device);

    PlaybackContext create_context_from_device(const PlaybackDevice &device, const std::vector<ALCint> &attrlist);

    template <std::size_t N>
    PlaybackContext create_context_from_device(const PlaybackDevice &device, const std::array<ALCint, N> &attrlist)
    {
        PlaybackContext context;
        context.create(device, attrlist);
        return context;
    }

} // namespace al_wrapper
