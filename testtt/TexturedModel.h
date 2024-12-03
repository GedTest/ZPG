#pragma once
#include "Model.h"
#include "Texture.h"


class TexturedModel : public ZPG::Model {
private:
    Texture* texture;

public:
    TexturedModel(const float points[], size_t count, Material* material, const std::string& texturePath);
    ~TexturedModel() override;

    void draw() const override;

    Texture* getTexture() const override { return this->texture; }
};
