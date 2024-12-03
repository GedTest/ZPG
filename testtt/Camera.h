#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Subject.h"


class Camera : public Subject {
private:
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
	float alpha;
	float phi;
	float aspectRatio;

	void limitAngle();

public:
	Camera();
	Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up, float aspectRatio=4.0f/3.0f);
	
	glm::mat4 lookAt() const;
	glm::vec3 getTarget() const;
	glm::mat4 getProjectionMatrix() const;

	void move(const glm::vec3& offset);
	void rotate(float xoffset, float yoffset, float sensitivity);

	glm::vec3 getEye() const { return eye; }

	void setAspectRatio(float aspectRatio);
};
