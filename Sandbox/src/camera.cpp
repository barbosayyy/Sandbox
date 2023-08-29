#include "camera.h"

Camera::Camera(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
	front = glm::vec3(0.0f, 0.0f, 1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	lookAt = glm::lookAt(position, position + front, up);

	Input::InputListener::getInstance()->addInputFunction([this]() {onInput(); });
}

Camera::~Camera()
{
}

void Camera:: updatePosition()
{
	lookAt = glm::lookAt(position, position + front, up);
}

void Camera::onInput()
{
	if (Input::InputListener::getInstance()->pressedKey(GLFW_KEY_W))
	{
		position.z += 0.1;
	}
	else if (Input::InputListener::getInstance()->pressedKey(GLFW_KEY_A))
	{
		position.x += 0.1;
	}
	else if (Input::InputListener::getInstance()->pressedKey(GLFW_KEY_S))
	{
		position.z -= 0.1;
	}
	else if (Input::InputListener::getInstance()->pressedKey(GLFW_KEY_D))
	{
		position.x -= 0.1;
	}
	updatePosition();
}
