#include "ComposedTransform.h"

#include <iostream>

using std::cerr;

#define RED_COLOR     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"


ComposedTransform::~ComposedTransform() {
    for (AbstractTransform* transform : this->transforms) {
        delete transform;
    }
}

void ComposedTransform::addTransform(AbstractTransform* transform) {
    this->transforms.push_back(transform);
}

void ComposedTransform::removeTransform(int index) {
    if (index >= this->transforms.size()) {
        cerr << RED_COLOR << "ERROR index out of bounds: " << index << COLOR_RESET << "\n";
        return;
    }
    
    AbstractTransform* saved = this->transforms[index];
    this->transforms.erase(this->transforms.begin() + index);
    delete saved;
    return;
}

void ComposedTransform::swapTransforms(int index1, int index2) {
    if (index1 >= this->transforms.size() || index2 >= this->transforms.size()) {
        int index = index1 >= this->transforms.size() ? index1 : index2;
        cerr << RED_COLOR << "ERROR index out of bounds: " << index << COLOR_RESET << "\n";
        return;
    }
    auto temp = this->transforms[index1];
    this->transforms[index1] = this->transforms[index2];
    this->transforms[index2] = temp;

    return;
}

void ComposedTransform::removeAll() {
    this->transforms.clear();
}

AbstractTransform* ComposedTransform::getTransformAt(int index) {
    if (index >= this->transforms.size()) {
        cerr << RED_COLOR << "ERROR index out of bounds: " << index << COLOR_RESET << "\n";
        return nullptr;
    }
    return this->transforms[index];
}

glm::mat4 ComposedTransform::getTransformMatrix() const {
    glm::mat4 result(1.0f);
    for (const AbstractTransform* transform : this->transforms) {
        result *= transform->getTransformMatrix();
    }
    return result;
}
