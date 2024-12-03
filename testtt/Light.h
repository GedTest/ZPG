#pragma once
#include <glm/vec3.hpp>
#include "Subject.h"


class Light : public Subject {
public:
    enum class LightType {
        POINT,
        DIRECTIONAL,
        SPOT
    };

private:
    LightType type;
    glm::vec3 position = glm::vec3(0, 0, 0);      // Used by point and spot lights
    glm::vec3 direction = glm::vec3(1, 0, 0);     // Used by directional and spot lights
    glm::vec3 color;

    // used by point and spot lights
    float constantAttenuation = 1.0f;
    float linearAttenuation = 0.0f;
    float quadraticAttenuation = 0.0f;

    // Spot light parameters
    float cutOffAngle = 0.0f;
    float outerCutOffAngle = 0.0f;

    // disable other constructor options
    Light() = delete;
    Light(const Light& other) = delete;
    Light& operator=(const Light& other) = delete;
    Light(LightType type);


public:
    static Light* createPointLight(
        const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
        const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f),
        float constantAttenuation = 1.0f,
        float linearAttenuation = 0.0f,
        float quadraticAttenuation = 0.0f
    );

    static Light* createDirectionalLight(
        const glm::vec3& direction = glm::vec3(0.0f, -1.0f, 0.0f),
        const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f)
    );

    static Light* createSpotLight(
        const glm::vec3& position = glm::vec3(0.0f, 0.0f, 0.0f),
        const glm::vec3& direction = glm::vec3(0.0f, -1.0f, 0.0f),
        const glm::vec3& color = glm::vec3(1.0f, 1.0f, 1.0f),
        float constantAttenuation = 1.0f,
        float linearAttenuation = 0.0f,
        float quadraticAttenuation = 0.0f,
        float cutOffAngle = 0.0f,
        float outerCutOffAngle = 15.0f
    );

    void setPosition(glm::vec3 position);
    void setDirection(const glm::vec3& direction);
    void setCutOffAngle(float innerAngle, float outerAngle);

    LightType getType() const;
    glm::vec3 getPosition() const;
    glm::vec3 getDirection() const;
    glm::vec3 getColor() const;
    float getConstantAttenuation() const;
    float getLinearAttenuation() const;
    float getQuadraticAttenuation() const;
    float getCutOffAngle() const;
    float getOuterCutOffAngle() const;
};
