#pragma once

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "input.h"

class Camera {
public:
	Camera(float x, float y, float z);
	~Camera();

	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	glm::mat4 lookAt;

	void updatePosition();

	void onInput();
};