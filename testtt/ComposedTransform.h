#pragma once
#include <vector>
#include "AbstractTransform.h"


class ComposedTransform : public AbstractTransform {
private:
    std::vector<AbstractTransform*> transforms;
public:
    ~ComposedTransform();
    void addTransform(AbstractTransform* transform);
    void removeTransform(int index);
    void swapTransforms(int index1, int index2);
    void removeAll();
    AbstractTransform* getTransformAt(int index);
    glm::mat4 getTransformMatrix() const override;
};
