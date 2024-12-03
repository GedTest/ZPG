#include "RandomTranslation.h"


RandomTranslation::RandomTranslation(bool setX, bool setY, bool setZ) {
	setTranslation(randomOffset(setX, setY, setZ));
}

glm::vec3 RandomTranslation::randomOffset(bool setX, bool setY, bool setZ) {
	float x = 0;
	float y = 0;
	float z = 0;

	if (setX == true) {
		int sign = this->random(1) > 0.5 ? -1 : 1;
		x = sign * this->random(80);
	}
	if (setY == true) {
		int sign = this->random(1) > 0.5 ? -1 : 1;
		y = sign * this->random(80);
	}
	if (setZ == true) {
		int sign = this->random(1) > 0.5 ? -1 : 1;
		z = sign * this->random(80);
	}
	return glm::vec3(x, y, z);
}
