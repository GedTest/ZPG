#include "PointLight.h"


PointLight::PointLight(const glm::vec3& position, const glm::vec3& color) {
    this->position = position;
    this->color = color;
}

void PointLight::setPosition(const glm::vec3& newPosition) {
    this->position = newPosition;
    this->notify();
}

void PointLight::setColor(const glm::vec3& newColor) {
    color = newColor;
    this->notify();
}

glm::vec3 PointLight::getPosition() const {
    return this->position;
}

glm::vec3 PointLight::getColor() const {
    return this->color;
}
