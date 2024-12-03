#include "Light.h"
#include <glm/glm.hpp>


Light::Light(LightType type) : type(type) {}

Light* Light::createPointLight(const glm::vec3& position, const glm::vec3& color, float constantAttenuation, float linearAttenuation, float quadraticAttenuation) {
    Light* light = new Light(LightType::POINT);
    light->position = position;
    light->color = color;
    light->constantAttenuation = constantAttenuation;
    light->linearAttenuation = linearAttenuation;
    light->quadraticAttenuation = quadraticAttenuation;
    return light;
}

Light* Light::createDirectionalLight(const glm::vec3& direction, const glm::vec3& color) {
    Light* light = new Light(LightType::DIRECTIONAL);
    light->direction = glm::normalize(direction);
    light->color = color;
    return light;
}

Light* Light::createSpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color, float constantAttenuation, float linearAttenuation, float quadraticAttenuation, float cutOffAngle, float outerCutOffAngle) {
    Light* light = new Light(LightType::SPOT);
    light->position = position;
    light->direction = glm::normalize(direction);
    light->color = color;
    light->constantAttenuation = constantAttenuation;
    light->linearAttenuation = linearAttenuation;
    light->quadraticAttenuation = quadraticAttenuation;
    light->cutOffAngle = glm::radians(cutOffAngle);
    light->outerCutOffAngle = glm::radians(outerCutOffAngle);
    return light;
}

Light::LightType Light::getType() const {
    return type;
}

glm::vec3 Light::getDirection() const {
    return direction;
}

float Light::getCutOffAngle() const {
    return cutOffAngle;
}

float Light::getOuterCutOffAngle() const {
    return outerCutOffAngle;
}

glm::vec3 Light::getPosition() const {
    return this->position;
}

glm::vec3 Light::getColor() const {
    return this->color;
}

float Light::getConstantAttenuation() const {
    return this->constantAttenuation;
}

float Light::getLinearAttenuation() const {
    return this->linearAttenuation;
}

float Light::getQuadraticAttenuation() const {
    return this->quadraticAttenuation;
}

void Light::setPosition(glm::vec3 position) {
    if (this->type != LightType::DIRECTIONAL) {
        this->position = position;
        this->notify();
    }
    return;
}

void Light::setDirection(const glm::vec3& direction) {
    if (this->type != LightType::POINT) {
        this->direction = glm::normalize(direction);
        notify();
    }
}

void Light::setCutOffAngle(float innerAngle, float outerAngle) {
    if (this->type == LightType::SPOT) {
        this->cutOffAngle = glm::radians(innerAngle);
        this->outerCutOffAngle = glm::radians(outerAngle);
        notify();
    }
}
