#include "RandomScale.h"


RandomScale::RandomScale(float maxScale) {
    float scaleFactor = random(maxScale);
    setScale(glm::vec3(scaleFactor, scaleFactor, scaleFactor));
}

RandomScale::RandomScale(float maxScaleX, float maxScaleY, float maxScaleZ) {
    int sign = this->random(1) > 0.5 ? -1 : 1;
    float x = sign * random(maxScaleX);
    
    sign = this->random(1) > 0.5 ? -1 : 1;
    float y = sign * random(maxScaleY);
    
    sign = this->random(1) > 0.5 ? -1 : 1;
    float z = sign * random(maxScaleZ);
    
    setScale(glm::vec3(x, y, z));
}
