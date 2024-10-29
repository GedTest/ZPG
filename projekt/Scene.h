#pragma once
#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Camera.h"


class Scene
{
private:
    std::vector<DrawableObject*> drawableObjects;
    std::vector<ShaderProgram*> shaderPrograms;
    ShaderProgram::ShaderType currentShaderType = ShaderProgram::ShaderType::PHONG;

public:
    Scene();
    ~Scene();

    Camera camera;
    
    void addDrawableObject(DrawableObject* drawableOject);
    void addShaderProgram(ShaderProgram* shaderProgram);
    void draw();

    void cycleLightShaders();
};
