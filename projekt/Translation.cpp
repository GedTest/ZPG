#include "Translation.h"


Translation::Translation(const glm::vec3& offset) {
    this->offset = offset;
}

void Translation::setTranslation(const glm::vec3& offset) {
    this->offset = offset;
}

glm::mat4 Translation::getTransformMatrix() const {
    return glm::translate(glm::mat4(1.0f), this->offset);
}
