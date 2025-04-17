#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

namespace SbEngine{
    using vec4 = glm::vec4;
    using vec3 = glm::vec3;
    using vec2 = glm::vec2;

    using mat2 = glm::mat2;
    using mat3 = glm::mat3;
    using mat4 = glm::mat4;

    constexpr vec3 Yaw_Right	{0.0f,0.0f,1.0f};
    constexpr vec3 Yaw_Left		{0.0f,0.0f,-1.0f};
    constexpr vec3 Roll_Right	{0.0f,1.0f,0.0f};
    constexpr vec3 Roll_Left	{0.0f,-1.0f,0.0f};
    constexpr vec3 Pitch_Up		{1.0f,0.0f,0.0f};
    constexpr vec3 Pitch_Down	{-1.0f,0.0f,0.0f};
}
