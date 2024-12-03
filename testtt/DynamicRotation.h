#pragma once
#include "Rotation.h"
#include <GLFW/glfw3.h>


class DynamicRotation : public Rotation {
private:
    float speed;
    float startTime;
public:
    DynamicRotation(float angle=0.0f, const glm::vec3& axis=glm::vec3(0.0f, 1.0f, 0.0f), float speed=10.0f) : Rotation(angle, axis) {
        this->speed = speed;
        this->startTime = glfwGetTime();
    }

    virtual glm::mat4 getTransformMatrix() const override {
        float currentTime = glfwGetTime();
        float elapsedTime = currentTime - this->startTime;
        float dynamicAngle = fmod(this->angle + elapsedTime * this->speed, 360.0f);

        return glm::rotate(glm::mat4(1.0f), glm::radians(dynamicAngle), this->axis);
    }
};
