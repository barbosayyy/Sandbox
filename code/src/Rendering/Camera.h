#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Core/Base.h"
#include "Math/Vectors.h"

namespace SbEngine{
	enum class CameraProjectionMode{
		CAMERA_PROJECTION_PERSPECTIVE 	= 0,
		CAMERA_PROJECTION_ORTHO			= 1
	};

	constexpr float CAMERA_DEFAULT_NEAR = 0.1;
	constexpr float CAMERA_DEFAULT_FAR = 500.0;
	
	class Camera {
	public:
		Camera(float x, float y, float z);
		~Camera();

		void UpdatePosition();
		
		void OnInput();
		void OnMouseAxisMove(float xOffset, float yOffset);
		CameraProjectionMode GetProjectionMode() const {return _projMode;};
		
		mat4 GetView();
		
		void SetProjectionMode(const CameraProjectionMode& projMode) {_projMode = projMode;};

		vec3 _position;
		vec3 _front;
		vec3 _up;
		float _pitch;
		float _yaw;
		float _roll;
		float _sensitivity = 0.1;
		float _moveSpeed = 0.1;
		bool _canMove = false;
		float _near;
		float _far;
		mat4 _lookAt;

		private:
			const float _defaultDirection = 90.0f;
			void Move(glm::vec3 direction, bool positive);

		float _lastCameraMouseX = 0.0f;
		float _lastCameraMouseY = 0.0f;
		CameraProjectionMode _projMode;
	};
}

