#pragma once
#include "Model.h"
#include "ShaderProgram.h"
#include "ComposedTransform.h"
#include <glm/vec3.hpp>


class DrawableObject
{
private:
    ZPG::Model* model;
    ShaderProgram* shaderProgram;
    ComposedTransform* transform;
    int startVertex;
    int vertexCount;

    glm::vec3 color;

    float random(float limit);

public:
    DrawableObject(ShaderProgram* program, ZPG::Model* model, int startVertex, int vertexCount, glm::vec3 color=glm::vec3(0.385f, 0.647f, 0.812f));
    ~DrawableObject();

    void draw();
    void move(const glm::vec3& offset);
    void rotate(float angle, const glm::vec3& axis);
    void scale(const glm::vec3& factor);

    void randomTransform();
    void setShaderType(ShaderProgram::ShaderType type);
};
