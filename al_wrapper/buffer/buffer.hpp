#pragma once

#include <vector>
#include <array>
#include "../base/al_resource.hpp"

namespace al_wrapper
{
    BASE_DECLARE_REF_TYPE(Buffer);

    /// @brief 缓冲区对象
    class Buffer : public ALResource
    {
    public:
        /// @brief 格式
        enum class Format : ALenum
        {
            Mono8 = AL_FORMAT_MONO8,
            Mono16 = AL_FORMAT_MONO16,
            Stereo8 = AL_FORMAT_STEREO8,
            Stereo16 = AL_FORMAT_STEREO16,
        };

        /// @brief 参数名
        enum class ParameterName : ALenum
        {
            Frequency = AL_FREQUENCY,
            Bits = AL_BITS,
            Channels = AL_CHANNELS,
            Size = AL_SIZE,
        };

    public:
        Buffer() = default;
        Buffer(Buffer &&from);
        ~Buffer() override;
        BASE_DELETE_COPY_FUNCTION(Buffer);

    public:
        Buffer &operator=(Buffer &&from);
        base::Int64 get_resource_type() const override;

    public:
        void create();
        void destroy();

    public:
        void set_data(Format format, const ALvoid *data, ALsizei size, ALsizei samplerate);
        void set_mono_data(const std::vector<base::Int8> &data, ALsizei samplerate = 44100);
        void set_mono_data(const std::vector<base::Int16> &data, ALsizei samplerate = 44100);
        void set_stereo_data(const std::vector<base::Int8> &data, ALsizei samplerate = 44100);
        void set_stereo_data(const std::vector<base::Int16> &data, ALsizei samplerate = 44100);

        template <typename T>
        void set_data(Format format, const std::vector<T> &data, ALsizei samplerate)
        {
            set_data(format, data.data(), data.size() * sizeof(T), samplerate);
        }

    public:
        void set_parameter(ParameterName param, ALint value);
        void get_parameter(ParameterName param, ALint &result) const;

        template <typename T>
        T get_parameter(ParameterName param) const
        {
            T result;
            get_parameter(param, result);
            return result;
        }
    };

    Buffer create_buffer();
    BufferRef create_buffer_shared();
    BufferUniqueRef create_buffer_unique();

    Buffer create_buffer_from_mono_data(const std::vector<base::Int8> &data, ALsizei samplerate = 44100);
    Buffer create_buffer_from_mono_data(const std::vector<base::Int16> &data, ALsizei samplerate = 44100);
    Buffer create_buffer_from_stereo_data(const std::vector<base::Int8> &data, ALsizei samplerate = 44100);
    Buffer create_buffer_from_stereo_data(const std::vector<base::Int16> &data, ALsizei samplerate = 44100);

} // namespace al_wrapper
