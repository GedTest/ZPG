#pragma once
#include <glm/vec3.hpp>
#include "Subject.h"


class PointLight : public Subject {
private:
    glm::vec3 position;
    glm::vec3 color;

public:
    PointLight(const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f), const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f));

    void setPosition(const glm::vec3& newPosition);
    void setColor(const glm::vec3& newColor);

    glm::vec3 getPosition() const;
    glm::vec3 getColor() const;
};
