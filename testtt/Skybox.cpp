#include "Skybox.h"
#include <glm/gtc/type_ptr.hpp>
#include "Translation.h"
#include "CubemapModel.h"


const float skyboxVertices[] = {
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};


Skybox::Skybox(const vector<string>& faces, Camera* camera) {
    this->camera = camera;
    this->camera->subscribe(this);

    CubemapModel* model = new CubemapModel(skyboxVertices, sizeof(skyboxVertices), new Material());
    this->shaderProgram = new ShaderProgram(ShaderProgram::ShaderType::SKYBOX, this->camera);
    this->texture = new CubemapTexture(faces);
    this->drawableObject = new DrawableObject(this->shaderProgram, model, glm::vec3(1, 0, 0));

    this->followCamera = true;
}

Skybox::~Skybox() {
    this->camera->unsubscribe(this);
    delete this->drawableObject;
    delete this->texture;
    delete this->shaderProgram;
}

void Skybox::draw() {
    this->texture->bind(0);
    this->shaderProgram->setSkybox();

    this->drawableObject->draw();
    return;
}

void Skybox::update() {
    if (this->camera && this->followCamera) {
        glm::vec3 cameraPosition = this->camera->getEye();
        ComposedTransform* transformComposite = dynamic_cast<ComposedTransform*>(drawableObject->transform);
        if (transformComposite) {
            transformComposite->removeAll();
            transformComposite->addTransform(new Translation(cameraPosition));
        }
    }
    return;
}

void Skybox::toggleFollowCamera() {
    this->followCamera = !this->followCamera;
    return;
}
