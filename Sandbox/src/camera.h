#pragma once

#include <glm.hpp>

class Camera {
public:
	Camera(float x, float y, float z);
	~Camera();
private:
	glm::vec3 position;
};