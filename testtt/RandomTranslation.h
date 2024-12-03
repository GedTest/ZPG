#pragma once
#include "Translation.h"


class RandomTranslation : public Translation {
//private:

public:
    glm::vec3 randomOffset(bool setX, bool setY, bool setZ);
    RandomTranslation(bool setX=true, bool setY=true, bool setZ=true);
};
