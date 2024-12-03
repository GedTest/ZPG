#include "Texture.h"


Texture::Texture(const string& filename, GLenum textureUnit) {
    GLuint i = 1;
    for (; i < MAX_TEXTURE_UNITS; i++) {
        if (this->textureUnits[i] == GL_TEXTURE1+textureUnit) { break; }
        if (this->textureUnits[i] == 0) {
            this->textureUnits[i] = GL_TEXTURE1+textureUnit;
            break;
        }

    }
    this->assignedUnit = this->textureUnits[i];

    if (!this->loadTexture(filename)) {
        std::cerr << "Failed to load " << filename << " texture.\n";
        exit(EXIT_FAILURE);
    }
    this->bind(this->assignedUnit);
}

Texture::~Texture() {
    if (this->textureID != 0) {
        glDeleteTextures(1, &this->textureID);
    }
}

bool Texture::loadTexture(const std::string& filename) {
    this->textureID = SOIL_load_OGL_texture(filename.c_str(), SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

    if (this->textureID == 0) {
        std::cerr << "An error occurred while loading texture: " << filename << std::endl;
        std::cerr << "SOIL error: " << SOIL_last_result() << std::endl;
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, this->textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    return true;
}

void Texture::bind(GLenum textureUnit) const {
    glActiveTexture(textureUnit);
    glBindTexture(GL_TEXTURE_2D, this->textureID);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::activateUnit(GLenum textureUnit) {
    glActiveTexture(textureUnit);
}
