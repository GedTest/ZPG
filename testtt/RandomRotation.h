#pragma once
#include "Rotation.h"


class RandomRotation : public Rotation {
private:
    glm::vec3 randomAxis(bool setX, bool setY, bool setZ);

public:
    RandomRotation(float maxAngle=360, bool setX=true, bool setY=true, bool setZ=true);
};
