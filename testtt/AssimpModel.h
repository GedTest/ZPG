#pragma once
#include "AbstractModel.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
#include "VertexArrayObject.h"
#include "VertexBufferObject.h"


class AssimpModel : public AbstractModel {
private:
    GLuint IBO = 0;
    VertexArrayObject* vao;
    VertexBufferObject* vbo;
    int indicesCount = 0;
    Texture* texture;
    Material* material;

    void loadModel(const std::string& path, const std::string& texturePath);

public:
    AssimpModel(const std::string& path, Material* material, const std::string& texturePath="None");
    ~AssimpModel() override;
    void draw() const override;
    Material* getMaterial() const override { return material; }
    Texture* getTexture() const override { return this->texture; }
};

