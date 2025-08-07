#pragma once

#include "Math/Vectors.h"

namespace Sb {
	enum class CameraProjectionMode{
		CAMERA_PROJECTION_PERSPECTIVE 	= 0,
		CAMERA_PROJECTION_ORTHO			= 1
	};

	constexpr float CAMERA_DEFAULT_FOV = 60.0f;
	constexpr float CAMERA_DEFAULT_DIRECTION = 90.0f;
	constexpr float CAMERA_DEFAULT_NEAR = 0.1;
	constexpr float CAMERA_DEFAULT_FAR = 500.0;
	
	class Camera {
	public:
		Camera(float x, float y, float z);
		~Camera();

		void UpdatePosition();
		void OnInput();
		void OnMouseAxisMove(float xOffset, float yOffset);
		void GenerateProjection(int viewportWidth, int viewportHeight);
		
		mat4 GetView() const { return _lookAt; };
		mat4 GetProjection() const { return _projection; };
		CameraProjectionMode GetProjectionMode() const { return _projMode; };
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
		float _fov;
		mat4 _lookAt;

	private:
		void Move(glm::vec3 direction, bool positive);
		
		mat4 _projection;
		CameraProjectionMode _projMode;
		float _lastCameraMouseX = 0.0f;
		float _lastCameraMouseY = 0.0f;
	};
}

