#pragma once
#include "DrawableObject.h"
#include "Light.h"
#include "RandomTranslation.h"
#include "../Models/sphere.h"
#include "Model.h"


class Firefly : public DrawableObject {
private:
    Light* light;
    RandomTranslation translator;
    int frameCounter;
    const int UPDATE_INTERVAL = 20;
    const float HEIGHT_MIN = 0.0f;
    const float HEIGHT_MAX = 1.0f;

public:
    //, nullptr
    Firefly(ShaderProgram* program, ZPG::Model* model, const glm::vec3& position, const glm::vec3& color)
        : DrawableObject(program, model, color),
        translator(true, true, true),
        frameCounter(0)
    {
        this->light = Light::createPointLight(position, color, 1.0f, 0.2f, 0.2f);
        move(position);
        scale(glm::vec3(0.1f, 0.1f, 0.1f));
    }

    ~Firefly() {
        delete this->light;
    }

    void draw() override {
        DrawableObject::draw();

        frameCounter++;
        if (this->frameCounter >= UPDATE_INTERVAL) {
            RandomTranslation* newPos = new RandomTranslation(true, false, true);
            move(newPos);

            glm::mat4 modelMatrix = this->transform->getTransformMatrix();
            int lightBeneath = -1;
            glm::vec3 pos(modelMatrix[3][0], modelMatrix[3][1] + lightBeneath, modelMatrix[3][2]);
            this->light->setPosition(pos);
            this->frameCounter = 0;
        }
    }

    Light* getLight() const {
        return this->light;
    }
};
