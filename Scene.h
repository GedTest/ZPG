#pragma once
#include <vector>
#include <unordered_map>
#include "DrawableObject.h"
#include "ShaderProgram.h"


class Scene
{
private:
    std::vector<DrawableObject*> drawableObjects;
    std::unordered_map<const char*, ShaderProgram*> shaderPrograms;

public:
    Scene() {};
    ~Scene();

    void addDrawableObject(DrawableObject* drawableOject);
    void addShaderProgram(const char* name, ShaderProgram* shaderProgram);
    void draw();
    ShaderProgram* getShaderProgram(const char* name);
};
