#pragma once
#include "Observer.h"
#include "Camera.h"
#include "Light.h"


class Flashlight : public Observer {
private:
    Camera* camera;
    Light* light;

public:
    Flashlight(Camera* camera) : camera(camera) {
        this->light = Light::createSpotLight(
            camera->getEye(),
            glm::vec3(0, 0, -1),
            glm::vec3(0.0f, 1.0f, 1.0f),
            1.0f,
            0.09f,
            0.032f,
            12.5f,
            17.5f
        );
        camera->subscribe(this);
    }

    Flashlight(Camera* camera,
        const glm::vec3& color,
        float constantAttenuation = 1.0f,
        float linearAttenuation = 0.09f,
        float quadraticAttenuation = 0.032f,
        float cutOffAngle = 12.5f,
        float outerCutOffAngle = 17.5f) : camera(camera) {

        this->light = Light::createSpotLight(
            camera->getEye(),
            glm::vec3(0, 0, -1),
            color,
            constantAttenuation,
            linearAttenuation,
            quadraticAttenuation,
            cutOffAngle,
            outerCutOffAngle
        );
        camera->subscribe(this);
    }

    ~Flashlight() {
        if (this->camera) {
            this->camera->unsubscribe(this);
        }
        delete this->light;
        this->light = nullptr;
    }

    virtual void update() override {
        glm::vec3 target = this->camera->getTarget();
        glm::vec3 eye = this->camera->getEye();
        glm::vec3 direction = glm::normalize(target - eye);

        this->light->setPosition(eye);
        this->light->setDirection(direction);
    }

    Light* getLight() const {
        return this->light;
    }
};
