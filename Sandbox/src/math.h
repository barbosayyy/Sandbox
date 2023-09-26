#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

using vec4 = glm::vec4;
using vec3 = glm::vec3;
using vec2 = glm::vec2;

using mat2 = glm::mat2;
using mat3 = glm::mat3;
using mat4 = glm::mat4;

#define Yaw_Right		vec3(0.0f, 0.0f, 1.0f)
#define Yaw_Left		vec3(0.0f, 0.0f, -1.0f)
#define Roll_Right		vec3(0.0f, 1.0f, 0.0f)
#define Roll_Left		vec3(0.0f, -1.0f, 0.0f)
#define Pitch_Up		vec3(1.0f, 0.0f, 0.0f)
#define Pitch_Down		vec3(-1.0f, 0.0f, 0.0f)