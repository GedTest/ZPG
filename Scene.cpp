#include "Scene.h"


Scene::~Scene()
{
    for (auto drawableObject : drawableObjects) {
        delete drawableObject;
    }
    for (auto& pair : shaderPrograms) {
        delete pair.second;
    }
}

void Scene::addDrawableObject(DrawableObject* drawableOject)
{
    this->drawableObjects.push_back(drawableOject);
    return;
}

void Scene::addShaderProgram(const char* name, ShaderProgram* shaderProgram)
{
    this->shaderPrograms[name] = shaderProgram;
    return;
}

void Scene::draw()
{
    for (const auto& drawableObject : drawableObjects) {
        drawableObject->draw();
    }
    return;
}

ShaderProgram* Scene::getShaderProgram(const char* name)
{
    return shaderPrograms[name];
}
