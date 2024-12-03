#include "RandomRotation.h"


glm::vec3 RandomRotation::randomAxis(bool setX, bool setY, bool setZ) {
	float x = 0;
	float y = 0;
	float z = 0;

	if (setX == true) {
		int sign = this->random(1) > 0.5 ? -1 : 1;
		x = sign * this->random(1);
	}
	if (setY == true) {
		int sign = this->random(1) > 0.5 ? -1 : 1;
		y = sign * this->random(1);
	}
	if (setZ == true) {
		int sign = this->random(1) > 0.5 ? -1 : 1;
		z = sign * this->random(1);
	}
	return glm::vec3(x, y, z);
}

RandomRotation::RandomRotation(float maxAngle,bool setX, bool setY, bool setZ) {
	float angle = random(maxAngle);
	glm::vec3 axis = this->randomAxis(setX, setY, setZ);
	setRotation(angle, axis);
}
