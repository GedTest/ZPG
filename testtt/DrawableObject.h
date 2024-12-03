#pragma once
#include "AbstractModel.h"
#include "ShaderProgram.h"
#include "ComposedTransform.h"
#include <glm/vec3.hpp>


class DrawableObject
{
private:
    AbstractModel* model;
    ShaderProgram* shaderProgram;
    glm::vec3 color;

    AbstractTexture* texture;

public:
    ComposedTransform* transform;
    
    DrawableObject(ShaderProgram* program, AbstractModel* model, glm::vec3 color=glm::vec3(0.385f, 0.647f, 0.812f));
    ~DrawableObject();

    virtual void draw();
    void move(const glm::vec3& offset);
    void move(class Translation* translation);
    void rotate(float angle, const glm::vec3& axis);
    void rotate(class Rotation* rotation);
    void rotateAroundPoint(Rotation* rotation, const glm::vec3& point);
    void scale(const glm::vec3& factor);
    void scale(class Scale* scale);

    void randomTransform();
    void setShaderType(ShaderProgram::ShaderType type);
};
