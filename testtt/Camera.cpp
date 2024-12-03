#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


Camera::Camera() {
	this->eye = glm::vec3(0, 0, 0);
	this->center = glm::vec3(0.0f, 0.0f, 0.0f);
	this->up = glm::vec3(0, 1, 0);
	this->alpha = glm::radians(90.0f);
	this->phi = 0.f;
	this->aspectRatio = 4.0f / 3.0f;
}

Camera::Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, float aspectRatio)
{
	this->eye = eye;
	this->center = center;
	this->up = up;
	this->alpha = glm::radians(90.0f);
	this->phi= 0.f;
	this->aspectRatio = aspectRatio;
}

glm::vec3 Camera::getTarget() const {
	return this->eye + glm::vec3(
		std::sin(alpha) * std::cos(phi),
		std::cos(alpha),
		std::sin(alpha) * std::sin(phi)
	);
}

void Camera::limitAngle()
{
	const float maxLimit = glm::radians<float>(179.0f);
	const float minLimit = glm::radians<float>(1.0f);

	if (this->alpha > maxLimit) {
		this->alpha = maxLimit;
	}
	else if (this->alpha < minLimit) {
		this->alpha = minLimit;
	}
	
	const float twoPi = glm::two_pi<float>();
	if (this->phi > twoPi) {
		this->phi -= twoPi;
	}
	else if (this->phi < 0) {
		this->phi += twoPi;
	}
}

glm::mat4 Camera::lookAt() const {
	return glm::lookAt(this->eye, this->getTarget(), this->up);
}

glm::mat4 Camera::getProjectionMatrix() const {
	return glm::perspective(glm::radians(45.0f), this->aspectRatio, 0.1f, 100.0f);
}

void Camera::move(const glm::vec3& offset) {
	glm::vec3 forward = glm::normalize(getTarget() - this->eye);
	glm::vec3 right = glm::normalize(glm::cross(forward, this->up));

	this->eye += right * offset.x + this->up * offset.y + forward * offset.z;
	
	this->notify();
}

void Camera::rotate(float xoffset, float yoffset, float sensitivity) {
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	this->phi += glm::radians(xoffset);
	this->alpha += glm::radians(yoffset);

	this->limitAngle();
	this->notify();
}

void Camera::setAspectRatio(float aspectRatio) {
	this->aspectRatio = aspectRatio;
}
