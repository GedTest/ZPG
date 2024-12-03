#pragma once
#include "AbstractModel.h"
#include <string>
#include <vector>


class ModelFactory {
public:
    enum class ModelType {
        Simple,
        Textured,
        Assimp
    };

    static AbstractModel* createModel(const float points[], size_t count, Material* material);
    static AbstractModel* createTexturedModel(const float points[], size_t count, Material* material, const std::string& texturePath);
    static AbstractModel* createAssimpModel(const std::string& path, Material* material, const std::string& texturePath="None");
};
