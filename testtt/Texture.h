#pragma once
#include "AbstractTexture.h"


class Texture : public AbstractTexture {
private:
    GLuint textureID;
    GLuint assignedUnit;

public:
    Texture(const string& filename, GLenum textureUnit = 0);
    ~Texture() override;

    bool loadTexture(const string& filename);
    void bind(GLenum textureUnit = GL_TEXTURE0) const override;
    void unbind() const override;

    GLuint getAssignedUnit() const override { return assignedUnit; }
    static void activateUnit(GLenum textureUnit);
};
