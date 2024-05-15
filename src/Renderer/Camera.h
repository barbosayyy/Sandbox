#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Core/Base.h"
#include "../Math/Vectors.h"

namespace Sandbox {
	enum class CameraProjectionMode{
		CAMERA_PROJECTION_PERSPECTIVE 	= 0,
		CAMERA_PROJECTION_ORTHO			= 1
	};
	
	class Camera {
	public:
		Camera(float x, float y, float z);
		~Camera();

		vec3 _position;
		vec3 _front;
		vec3 _up;
		float _pitch;
		float _yaw;
		float _roll;
		const float _sensitivity = 0.1;
		const float _moveSpeed = 0.1;
		bool _canMove = false;

		void UpdatePosition();
		void OnInput();
		void OnMouseAxisMove(float xOffset, float yOffset);
		CameraProjectionMode GetProjectionMode() const {return _projMode;};
		void SetProjectionMode(const CameraProjectionMode& projMode) {_projMode = projMode;};

		mat4 GetView();
	private:
		const float _defaultDirection = 90.0f;
		void Move(glm::vec3 direction, bool positive);

		float _lastCameraMouseX = 0.0f;
		float _lastCameraMouseY = 0.0f;
		mat4 _lookAt;
		CameraProjectionMode _projMode;
	};
}

