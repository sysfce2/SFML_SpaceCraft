#pragma once

#include "FPCamera.h"
#include "ArcBallCamera.h"
#include "CameraMoveDirection.h"

#include <list>
#include <string>

class CameraManager
{
public:
	CameraManager(Settings::CameraSettings* arcBallCameraSettings, Settings::CameraSettings* firstPersonCameraSettings, glm::vec2 windowSize);

	void addCameraMoveDirection(const CameraMoveDirection& direction);
	void removeCameraMoveDirection(const CameraMoveDirection& direction);

	void mouseControl(const glm::vec2& oldMousePosition, const glm::vec2& newMousePosition);
	void updateCameraPosition(const GLfloat& timeInSec);
	void useCamera(GLuint uniformView, GLuint uniformEyePosition, GLuint uniformProjection);
	void changeCamera();
	void drawAxis();

private:

	CameraInterface* currentCamera;
	FPCamera fpCamera;
	ArcBallCamera arcBallCamera;

	std::list<CameraMoveDirection> cameraMoveDirections;
	glm::mat4 projectionMatrix;
	glm::vec2 windowSize;

	void calculateProjectionMatrix();
};

