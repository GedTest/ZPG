#pragma once
#include <vector>
#include "AbstractTransform.h"


class ComposedTransform : public AbstractTransform {
private:
    std::vector<AbstractTransform*> children;

public:
    ~ComposedTransform();

    void addTransform(AbstractTransform* transform);

    glm::mat4 getTransformMatrix() const override;
};
