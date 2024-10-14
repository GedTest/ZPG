#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>


Transform::Transform() {
    this->setIdentity();
}

void Transform::translate(const glm::vec3& translation) {
    this->modelMatrix = glm::translate(this->modelMatrix, translation);
}

void Transform::rotate(float angle, const glm::vec3& axis) {
    this->modelMatrix = glm::rotate(this->modelMatrix, angle, axis);
}

void Transform::scale(const glm::vec3& scale) {
    this->modelMatrix = glm::scale(this->modelMatrix, scale);
}

void Transform::setIdentity() {
    this->modelMatrix = glm::mat4(1.0f);
}

glm::mat4 Transform::getTransformMatrix() const {
    return this->modelMatrix;
}
