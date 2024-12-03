#include "ModelFactory.h"
#include "AbstractModel.h"
#include "Model.h"
#include "TexturedModel.h"
#include "AssimpModel.h"


AbstractModel* ModelFactory::createModel(const float points[], size_t count, Material* material) {
    return new ZPG::Model(points, count, material);
}

AbstractModel* ModelFactory::createTexturedModel(const float points[], size_t count, Material* material, const std::string& texturePath) {
    return new TexturedModel(points, count, material, texturePath);
}

AbstractModel* ModelFactory::createAssimpModel(const std::string& path, Material* material, const std::string& texturePath) {
    return new AssimpModel(path, material, texturePath);
}
