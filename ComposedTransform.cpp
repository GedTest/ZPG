#include "ComposedTransform.h"


ComposedTransform::~ComposedTransform() {
    for (AbstractTransform* child : this->children) {
        delete child;
    }
}

void ComposedTransform::addTransform(AbstractTransform* transform) {
    this->children.push_back(transform);
}

glm::mat4 ComposedTransform::getTransformMatrix() const {
    glm::mat4 result(1.0f);
    for (const AbstractTransform* child : this->children) {
        result *= child->getTransformMatrix();
    }
    return result;
}
