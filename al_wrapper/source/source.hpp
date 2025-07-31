#pragma once

#include <array>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../base/al_resource.hpp"

namespace al_wrapper
{
    BASE_DECLARE_REF_TYPE(Source);
    class Buffer;

    /// @brief 声源
    class Source : public ALResource
    {
    public:
        /// @brief 参数名
        enum class ParameterName : ALenum
        {
            Pitch = AL_PITCH,
            Gain = AL_GAIN,
            MinGain = AL_MIN_GAIN,
            MaxGain = AL_MAX_GAIN,
            MaxDistance = AL_MAX_DISTANCE,
            RolloffFactor = AL_ROLLOFF_FACTOR,
            ConeOuterGain = AL_CONE_OUTER_GAIN,
            ConeInnerAngle = AL_CONE_INNER_ANGLE,
            ConeOuterAngle = AL_CONE_OUTER_ANGLE,
            ReferenceDistance = AL_REFERENCE_DISTANCE,

            Position = AL_POSITION,
            Velocity = AL_VELOCITY,
            Direction = AL_DIRECTION,

            Looping = AL_LOOPING,
            SourceRelative = AL_SOURCE_RELATIVE,
            Buffer = AL_BUFFER,
            SourceState = AL_SOURCE_STATE,
            BuffersQueued = AL_BUFFERS_QUEUED,
            BuffersProcessed = AL_BUFFERS_PROCESSED,
        };

        /// @brief 声源状态
        enum class State : ALenum
        {
            Initial = AL_INITIAL,
            Playing = AL_PLAYING,
            Paused = AL_PAUSED,
            Stopped = AL_STOPPED,
        };

    public:
        Source() = default;
        Source(Source &&from);
        ~Source() override;
        BASE_DELETE_COPY_FUNCTION(Source);

    public:
        Source &operator=(Source &&from);
        base::Int64 get_resource_type() const override;

    public:
        void create();
        void destroy();

    public:
        void play();
        void stop();
        void rewind();
        void pause();

        void set_buffer();
        void set_buffer(const Buffer &buffer);
        State get_state() const;

    public:
        void set_parameter(ParameterName param, ALint value);
        void set_parameter(ParameterName param, ALfloat value);
        void set_parameter(ParameterName param, const glm::ivec3 &value);
        void set_parameter(ParameterName param, const glm::vec3 &value);
        void get_parameter(ParameterName param, ALint &result) const;
        void get_parameter(ParameterName param, ALfloat &result) const;
        void get_parameter(ParameterName param, glm::ivec3 &value) const;
        void get_parameter(ParameterName param, glm::vec3 &value) const;

        template <typename T>
        T get_parameter(ParameterName param) const
        {
            T result;
            get_parameter(param, result);
            return result;
        }
    };

    Source create_source();
    SourceRef create_source_shared();
    SourceUniqueRef create_source_unique();

} // namespace al_wrapper
