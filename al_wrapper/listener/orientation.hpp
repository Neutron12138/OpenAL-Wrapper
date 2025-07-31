#pragma once

#include <glm/glm.hpp>
#include "../base/al.hpp"

namespace al_wrapper
{
    /// @brief 朝向
    class Orientation
    {
    public:
        glm::vec3 front;
        glm::vec3 up;

    public:
        constexpr Orientation()
            : front(glm::vec3(0.0f, 0.0f, -1.0f)),
              up(glm::vec3(0.0f, 1.0f, 0.0f)) {}
        constexpr Orientation(const glm::vec3 &f, const glm::vec3 &u)
            : front(f), up(u) {}
        inline ~Orientation() = default;

    public:
        inline operator ALfloat *() { return reinterpret_cast<ALfloat *>(this); }
        inline operator const ALfloat *() const { return reinterpret_cast<const ALfloat *>(this); }
    };

    static_assert(sizeof(Orientation) == 2 * sizeof(glm::vec3), "Layout error");

} // namespace al_wrapper
