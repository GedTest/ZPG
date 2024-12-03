#pragma once
#include <vector>
#include "DrawableObject.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Firefly.h"
#include "Flashlight.h"
#include "Skybox.h"


class Scene
{
private:
    std::vector<DrawableObject*> drawableObjects;
    std::vector<ShaderProgram*> shaderPrograms;
    ShaderProgram::ShaderType currentShaderType = ShaderProgram::ShaderType::PHONG;

    Flashlight* flashlight;
    Skybox* skybox;

public:
    Camera camera;

    Scene();
    ~Scene();
    
    void addFlashlight(Light* spotlight);
    void removeFlashLight();
    void addDrawableObject(DrawableObject* drawableOject);
    void addShaderProgram(ShaderProgram* shaderProgram);
    void addSkybox(const vector<string>& faces);
    void addFirefly(Firefly* firefly);

    void draw();
    void cycleLightShaders();
};
