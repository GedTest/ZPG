#include "Scene.h"


Scene::Scene()
{
    this->camera = Camera(
        glm::vec3(3, 0, 8),         // and looks at the origin
        glm::vec3(3, 0, 0),                // 10, 3, 10 Camera is at (4,3,-3), in World Space
        glm::vec3(0, 1, 0)                   // Head is up (set to 0,-1,0 to look upside-down)
    );
}

Scene::~Scene()
{
    for (auto drawableObject : this->drawableObjects) {
        delete drawableObject;
    }
    for (auto shaderProgram : this->shaderPrograms) {
        delete shaderProgram;
    }
}

void Scene::addDrawableObject(DrawableObject* drawableOject)
{
    this->drawableObjects.push_back(drawableOject);
    return;
}

void Scene::addShaderProgram(ShaderProgram* shaderProgram)
{
    this->shaderPrograms.push_back(shaderProgram);
    return;
}

void Scene::draw()
{
    for (const auto& drawableObject : this->drawableObjects) {
        drawableObject->draw();
    }
    
    return;
}

void Scene::cycleLightShaders()
{
    switch (this->currentShaderType) {
        case ShaderProgram::ShaderType::CONSTANT:
            this->currentShaderType = ShaderProgram::ShaderType::LAMBERT;
            break;
        case ShaderProgram::ShaderType::LAMBERT:
            this->currentShaderType = ShaderProgram::ShaderType::PHONG;
            break;
        case ShaderProgram::ShaderType::PHONG:
            this->currentShaderType = ShaderProgram::ShaderType::BLINN;
            break;
        case ShaderProgram::ShaderType::BLINN:
            this->currentShaderType = ShaderProgram::ShaderType::CONSTANT;
            break;
    }

    for (auto& object : this->drawableObjects) {
        object->setShaderType(this->currentShaderType);
    }

    std::cout << "Switched to shader type: " << static_cast<int>(this->currentShaderType) << std::endl;
}
