#pragma once
#include <GL/glew.h>
#include <SOIL.h>
#include <string>
#include <iostream>
#include <vector>
using std::string;
using std::vector;


class AbstractTexture {
protected:
	GLuint textureID;
	static vector<GLuint> textureUnits;
	static const int MAX_TEXTURE_UNITS = 32;

public:
	virtual ~AbstractTexture() = default;

	virtual void bind(GLenum textureUnit=0) const = 0;
	virtual void unbind() const = 0;
	virtual GLuint getAssignedUnit() const = 0;
};
