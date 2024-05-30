#include "Camera.h"
#include "../Core/Types.h"
#include "../Input/Input.h"

using namespace Sandbox;

Camera::Camera(float x, float y, float z)
{
	_position = glm::vec3(x, y, z);
	_front = glm::vec3(0.0f, 0.0f, 1.0f);
	_up = glm::vec3(0.0f, 1.0f, 0.0f);
	_pitch = 0.0f;
	_yaw = _defaultDirection;
	_roll = 0.0f;
	_lookAt = glm::lookAt(_position, _position + _front, _up);
	_projMode = CameraProjectionMode::CAMERA_PROJECTION_PERSPECTIVE;
	_near = CAMERA_DEFAULT_NEAR;
	_far = CAMERA_DEFAULT_FAR;

	InputManager::GetInstance()->AddInputFunction([this]() {OnInput(); });
	InputManager::GetInstance()->AddMouseAxisMoveFunction([this](float xOffset, float yOffset) {OnMouseAxisMove(InputManager::GetInstance()->xOffset, InputManager::GetInstance()->yOffset); });
}

Camera::~Camera()
{
}

void Camera:: UpdatePosition()
{
	_lookAt = glm::lookAt(_position, _position + _front, _up);
}

void Camera::Move(glm::vec3 direction, bool invert)
{
	if(invert)
		_position += direction * _moveSpeed;
	else
		_position -= direction * _moveSpeed;
}

void Camera::OnInput()
{
	if (InputManager::PressedMouse(SB_MOUSE_RIGHT) == SB_PRESS)
	{
		if (!_canMove)
			_canMove = true;
	}
	else if(InputManager::PressedMouse(SB_MOUSE_RIGHT) == SB_RELEASE)
	{
		if (_canMove)
			_canMove = false;
	}

	if (_canMove)
	{
		if (InputManager::PressedKey(SB_KEYBOARD_W))
		{
			Move(_front, true);
		}
		else if (InputManager::PressedKey(SB_KEYBOARD_A))
		{
			Move(glm::normalize(glm::cross(_front, _up)), false);
		}
		else if (InputManager::PressedKey(SB_KEYBOARD_S))
		{
			Move(_front, false);
		}
		else if (InputManager::PressedKey(SB_KEYBOARD_D))
		{
			Move(glm::normalize(glm::cross(_front, _up)), true);
		}
		UpdatePosition();
	}
}

void Camera::OnMouseAxisMove(float xOffset, float yOffset)
{
	if (_canMove)
	{
		xOffset *= _sensitivity;
		yOffset *= _sensitivity;

		_yaw += xOffset;
		_pitch += yOffset;

		if (_pitch > 89.0f)
			_pitch = 89.0f;
		if (_pitch < -89.0f)
			_pitch = -89.0f;

		while (_yaw > 360.0f)
			_yaw -= 360.0f;
		while (_yaw < 0.0f)
			_yaw += 360.0f;

		glm::vec3 dir;
		dir.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		dir.y = sin(glm::radians(_pitch));
		dir.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		_front = glm::normalize(dir);

		UpdatePosition();
	}
}

glm::mat4 Camera::GetView()
{
	return _lookAt;
}
