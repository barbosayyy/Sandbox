#include "camera.h"
#include "input.h"

using namespace Sandbox;

Camera::Camera(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
	front = glm::vec3(0.0f, 0.0f, 1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	pitch = 0.0f;
	yaw = defaultDirection;
	roll = 0.0f;
	lookAt = glm::lookAt(position, position + front, up);

	InputListener::getInstance()->addInputFunction([this]() {onInput(); });
	InputListener::getInstance()->addMouseAxisMoveFunction([this](float xOffset, float yOffset) {onMouseAxisMove(InputListener::getInstance()->xOffset, InputListener::getInstance()->yOffset); });
}

Camera::~Camera()
{
}

void Camera:: updatePosition()
{
	lookAt = glm::lookAt(position, position + front, up);
}

void Camera::move(glm::vec3 direction, bool positive)
{
	if(positive)
		position += direction * moveSpeed;
	else
		position -= direction * moveSpeed;
}

void Camera::onInput()
{
	if (InputListener::pressedMouse(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
	{
		if (!canMove)
			canMove = true;
	}
	else if(InputListener::pressedMouse(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE)
	{
		if (canMove)
			canMove = false;
	}

	if (canMove)
	{
		if (InputListener::pressedKey(GLFW_KEY_W))
		{
			move(front, true);
		}
		else if (InputListener::pressedKey(GLFW_KEY_A))
		{
			move(glm::normalize(glm::cross(front, up)), false);
		}
		else if (InputListener::pressedKey(GLFW_KEY_S))
		{
			move(front, false);
		}
		else if (InputListener::pressedKey(GLFW_KEY_D))
		{
			move(glm::normalize(glm::cross(front, up)), true);
		}
		updatePosition();
	}
}

void Camera::onMouseAxisMove(float xOffset, float yOffset)
{
	if (canMove)
	{
		xOffset *= sensitivity;
		yOffset *= sensitivity;

		yaw += xOffset;
		pitch += yOffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		while (yaw > 360.0f)
			yaw -= 360.0f;
		while (yaw < 0.0f)
			yaw += 360.0f;

		glm::vec3 dir;
		dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		dir.y = sin(glm::radians(pitch));
		dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(dir);

		updatePosition();
	}
}
