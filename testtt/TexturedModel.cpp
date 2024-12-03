#include "TexturedModel.h"


TexturedModel::TexturedModel(const float points[], size_t count, Material* material, const std::string& texturePath) : ZPG::Model(points, count, material) {
    this->vao->enableAttribute(3);

    this->vertexCount = count / sizeof(float) / 8;
    this->texture = new Texture(texturePath);
}

TexturedModel::~TexturedModel() {
    delete this->texture;
}

void TexturedModel::draw() const {
    this->texture->bind();
    ZPG::Model::draw();
    this->texture->unbind();
    return;
}
