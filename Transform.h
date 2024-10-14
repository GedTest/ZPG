#pragma once
#include "AbstractTransform.h"


class Transform : public AbstractTransform {
private:
    glm::mat4 modelMatrix;

public:
    Transform();

    void translate(const glm::vec3& translation);
    void rotate(float angle, const glm::vec3& axis);
    void scale(const glm::vec3& scale);

    void setIdentity();

    glm::mat4 getTransformMatrix() const override;
};
