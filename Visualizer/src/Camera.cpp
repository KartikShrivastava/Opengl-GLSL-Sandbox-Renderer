#include "Camera.h"

#include "gtx/transform.hpp"

const float Camera::MOVEMENT_SPEED = 0.1f;

Camera::Camera() : viewDirection(0.0f, -0.5f, -1.0f), UP(0.0f, 1.0f, 0.0f), position(0.0f, 5.0f, 5.0f) {
}

void Camera::MouseUpdate(const glm::vec2& newMousePosition) {
	glm::vec2 mouseDelta = newMousePosition - oldMousePosition;
	if (glm::length(mouseDelta) > 50.0f) {
		oldMousePosition = newMousePosition;
		return;
	}
	const float	ROTATION_SPEED = 0.1f;
	pitchAxis = glm::cross(viewDirection, UP);
	glm::mat4 rotationMatrix =	glm::rotate(-glm::radians(mouseDelta.x) * ROTATION_SPEED, UP) * 
								glm::rotate(-glm::radians(mouseDelta.y) * ROTATION_SPEED, pitchAxis);
	viewDirection = glm::mat3(rotationMatrix) * viewDirection;
	oldMousePosition = newMousePosition;
}

glm::mat4 Camera::GetWorldToViewMatrix() const{
	return glm::lookAt(position, position + viewDirection, UP);
}

void Camera::MoveForward() {
	position += MOVEMENT_SPEED * viewDirection;
}

void Camera::StrafeLeft() {
	position += -MOVEMENT_SPEED * pitchAxis;
}
void Camera::MoveBackward() {
	position += -MOVEMENT_SPEED * viewDirection;
}

void Camera::StrafeRight(){
	position += MOVEMENT_SPEED * pitchAxis;
}

void Camera::MoveUp() {
	position += MOVEMENT_SPEED * UP;
}

void Camera::MoveDown() {
	position += -MOVEMENT_SPEED * UP;
}