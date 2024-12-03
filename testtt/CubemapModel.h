#pragma once
#include "Model.h"


class CubemapModel : public ZPG::Model {
public:
	CubemapModel(const float points[], size_t count, Material* material);
};
