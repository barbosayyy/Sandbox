#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Sandbox {
	class Camera {
	public:
		Camera(float x, float y, float z);
		~Camera();

		glm::vec3 _position;
		glm::vec3 _front;
		glm::vec3 _up;
		float _pitch;
		float _yaw;
		float _roll;
		glm::mat4 _lookAt;
		const float _sensitivity = 0.1;
		const float _moveSpeed = 0.1;
		bool _canMove = false;

		void UpdatePosition();
		void OnInput();
		void OnMouseAxisMove(float xOffset, float yOffset);
	private:
		const float _defaultDirection = 90.0f;
		void Move(glm::vec3 direction, bool positive);

		float _lastCameraMouseX = 0.0f;
		float _lastCameraMouseY = 0.0f;
	};
}

