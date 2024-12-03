#include "Scene.h"
#include "Skybox.h"


Scene::Scene()
{
    this->camera = Camera(
        glm::vec3(3, 0, 8),         // and looks at the origin
        glm::vec3(3, 0, 0),         // 10, 3, 10 Camera is at (4,3,-3), in World Space
        glm::vec3(0, 1, 0)          // Head is up (set to 0,-1,0 to look upside-down)
    );

    this->flashlight = nullptr;
    this->skybox = nullptr;
}

Scene::~Scene()
{
    for (auto drawableObject : this->drawableObjects) {
        delete drawableObject;
    }
    for (auto shaderProgram : this->shaderPrograms) {
        delete shaderProgram;
    }

    this->removeFlashLight();
    delete this->skybox;
}

void Scene::addFlashlight(Light* spotlight) {
    this->removeFlashLight();

    this->flashlight = new Flashlight(
        &this->camera,
        spotlight->getColor(),
        spotlight->getConstantAttenuation(),
        spotlight->getLinearAttenuation(),
        spotlight->getQuadraticAttenuation(),
        glm::degrees(spotlight->getCutOffAngle()),
        glm::degrees(spotlight->getOuterCutOffAngle())
    );

    return;
}

void Scene::removeFlashLight() {
    if (this->flashlight) {
        Light* light = this->flashlight->getLight();
        for (auto& program : this->shaderPrograms) {
            program->removeLight(light);
        }
        delete this->flashlight;
        this->flashlight = nullptr;
    }
    return;
}

void Scene::addDrawableObject(DrawableObject* drawableOject)
{
    this->drawableObjects.push_back(drawableOject);
    return;
}

void Scene::addShaderProgram(ShaderProgram* shaderProgram)
{
    this->shaderPrograms.push_back(shaderProgram);

    if (this->flashlight) {
        shaderProgram->addLight(this->flashlight->getLight());
    }
    return;
}

void Scene::addSkybox(const vector<string>& faces) {
    if (this->skybox != nullptr) { delete this->skybox; }

    this->skybox = new Skybox(faces, &this->camera);
    return;
}

void Scene::addFirefly(Firefly* firefly) {
    this->addDrawableObject(firefly);

    for (auto& program : this->shaderPrograms) {
        program->addLight(firefly->getLight());
    }
    return;
}

void Scene::draw()
{
    if (this->skybox) {
        this->skybox->draw();
        glClear(GL_DEPTH_BUFFER_BIT);
    }

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

    std::cout << "Switched to shader type: " << static_cast<int>(this->currentShaderType) << "\n";
    return;
}
