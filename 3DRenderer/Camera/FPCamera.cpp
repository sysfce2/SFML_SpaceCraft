#include "FPCamera.h"
#include <glm/ext/matrix_transform.hpp>

FPCamera::FPCamera(glm::vec3 position, glm::vec3 worldUp, GLfloat yaw, GLfloat pitch, GLfloat moveSpeed, GLfloat turnSpeed)
	: CameraInterface(position, worldUp, moveSpeed, turnSpeed), yaw(yaw), pitch(pitch)
{
	this->updateCameraProperties();
}


void FPCamera::updateCameraPosition(const CameraMoveDirection& direction, const GLfloat& timeInSec)
{
	auto velocity = timeInSec * this->moveSpeed;

	switch (direction)
	{
	case(CameraMoveDirection::Forward):
		this->position += front * velocity;
		break;
	case(CameraMoveDirection::Backward):
		this->position -= front * velocity;
		break;
	case(CameraMoveDirection::Left):
		this->position -= right * velocity;
		break;
	case(CameraMoveDirection::Right):
		this->position += right * velocity;
		break;
	default:
		break;
	}
	this->updateCameraProperties();
}

void FPCamera::handleMouse(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition)
{
	auto change = newMousePosition - oldMousePosition;
	auto xChange = change.x * this->turnSpeed;
	auto yChange = change.y * this->turnSpeed;

	this->yaw += xChange;
	this->pitch -= yChange;

	if (this->pitch > 89.0f) {
		this->pitch = 89.0f;
	}
	else if (this->pitch < -89.0f) {
		this->pitch = -89.0f;
	}

	this->updateCameraProperties();
}

void FPCamera::updateCameraProperties()
{
	this->front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(pitch));
	this->front.y = sin(glm::radians(this->pitch));
	this->front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(this->front);

	this->right = glm::normalize(glm::cross(this->front, this->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));
}

glm::mat4 FPCamera::calculateViewMatrix() const
{
	return glm::lookAt(this->position, this->position + this->front, up);
}
