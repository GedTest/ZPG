#pragma once
#include <glm/vec3.hpp>
#include "AbstractTexture.h"


class Material {
public:
    glm::vec3 reflectance;
    float shininess;

    Material(
        const glm::vec3& reflectance = glm::vec3(0.1f, 1.0f, 1.0f),
        float shininess = 32.0f
    ) {
        this->reflectance = reflectance;
        this->shininess = shininess;
    }
};
