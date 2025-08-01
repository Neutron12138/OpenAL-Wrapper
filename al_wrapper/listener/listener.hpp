#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <base/misc/noncopyable_object.hpp>
#include "../base/al.hpp"
#include "orientation.hpp"

namespace al_wrapper
{
    /// @brief 监听器
    class Listener : public base::NoncopyableObject
    {
    public:
        /// @brief  参数名
        enum class ParameterName : ALenum
        {
            Gain = AL_GAIN,
            Position = AL_POSITION,
            Velocity = AL_VELOCITY,
            Orientation = AL_ORIENTATION,
        };

        static Listener &get_instance();

    private:
        Listener() = default;
        ~Listener() = default;
        BASE_DELETE_COPY_FUNCTION(Listener);

    public:
        void set_parameter(ParameterName param, ALint value);
        void set_parameter(ParameterName param, ALfloat value);
        void set_parameter(ParameterName param, const glm::ivec3 &value);
        void set_parameter(ParameterName param, const glm::vec3 &value);
        void set_parameter(ParameterName param, const Orientation &orientation);

        void get_parameter(ParameterName param, ALint &result) const;
        void get_parameter(ParameterName param, ALfloat &result) const;
        void get_parameter(ParameterName param, glm::ivec3 &result) const;
        void get_parameter(ParameterName param, glm::vec3 &result) const;
        void get_parameter(ParameterName param, Orientation &result) const;

        template <typename T>
        T get_parameter(ParameterName param) const
        {
            T result;
            get_parameter(param, result);
            return result;
        }

    public:
        void set_gain(ALfloat value);
        void set_position(const glm::vec3 &position);
        void set_velocity(const glm::vec3 &velocity);
        void set_orientation(const Orientation &orientation);

        ALfloat get_gain() const;
        glm::vec3 get_position() const;
        glm::vec3 get_velocity() const;
        Orientation get_orientation() const;
    };

} // namespace al_wrapper
