#include "camera.h"

Camera::Camera(float x, float y, float z)
{
	position = glm::vec3(x, y, z);
}

Camera::~Camera()
{

}