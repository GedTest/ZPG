#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "ComposedTransform.h"


class DrawableObject
{
private:
    ZPG::Model* model;
    ShaderProgram* shaderProgram;
    ComposedTransform* transform;
    int startVertex;
    int vertexCount;

    float angle = 0.01f;

    float random(float limit);

public:
    DrawableObject(ShaderProgram* program, ZPG::Model* model, int startVertex, int vertexCount);
    ~DrawableObject();

    void draw();
    void move(const glm::vec3& offset);
    void rotate(float angle, const glm::vec3& axis);
    void scale(const glm::vec3& factor);

    void randomTransform();
};
