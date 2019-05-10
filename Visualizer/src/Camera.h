#pragma once

#include "glm.hpp"

class Camera {
private:
	glm::vec3 position;
	glm::vec3 viewDirection;
	glm::vec3 UP;
	glm::vec2 oldMousePosition;
	static const float MOVEMENT_SPEED;
	glm::vec3 pitchAxis;
public:
	Camera();
	void MouseUpdate(const glm::vec2& newMousePosition);
	glm::mat4 GetWorldToViewMatrix() const;
	void MoveForward();
	void StrafeLeft();
	void MoveBackward();
	void StrafeRight();
	void MoveUp();
	void MoveDown();
};