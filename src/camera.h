#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "input.h"

namespace Sandbox {
	class Camera {
	public:
		Camera(float x, float y, float z);
		~Camera();

		glm::vec3 position;
		glm::vec3 front;
		glm::vec3 up;
		float pitch;
		float yaw;
		float roll;
		glm::mat4 lookAt;
		const float sensitivity = 0.1;
		const float moveSpeed = 0.1;
		bool canMove = false;

		void updatePosition();
		void onInput();
		void onMouseAxisMove(float xOffset, float yOffset);
	private:
		const float defaultDirection = 90.0f;
		void move(glm::vec3 direction, bool positive);

		float lastCameraMouseX = 0.0f;
		float lastCameraMouseY = 0.0f;
	};
}

