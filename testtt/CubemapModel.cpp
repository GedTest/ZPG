#include "CubemapModel.h"


CubemapModel::CubemapModel(const float points[], size_t count, Material* material) : ZPG::Model(points, count, material) {
    this->vao->enableAttribute(1);

    this->vertexCount = count / sizeof(float) / 3;
}
