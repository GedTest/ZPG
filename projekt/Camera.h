#pragma once
#include <GL/glew.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Subject.h"


class Camera
{
private:
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;
	float alpha;
	float phi;

	Subject subject;

	glm::vec3 getTarget() const;
	void limitAngle();

public:
	Camera();
	Camera(glm::vec3 eye, glm::vec3 center, glm::vec3 up);
	
	glm::mat4 lookAt() const;
	glm::mat4 getProjectionMatrix() const;

	void move(const glm::vec3& offset);
	void rotate(float xoffset, float yoffset, float sensitivity);

	void subscribe(Observer* observer);
	void unsubscribe(Observer* observer);
	glm::vec3 getEye() const { return eye; }

};
