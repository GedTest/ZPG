#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "Material.h"
#include "Texture.h"


class AbstractModel {
protected:
    int vertexCount;

public:
    virtual ~AbstractModel() = default;
    virtual void draw() const = 0;
    virtual Material* getMaterial() const = 0;
    virtual Texture* getTexture() const = 0;
};
