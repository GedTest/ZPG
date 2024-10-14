#pragma once
#include <GL/glew.h>


class BaseShader
{
private:
	GLuint shaderID;

public:
	BaseShader(GLenum shaderType, const char* source);
	virtual ~BaseShader();

	GLuint getID() const;
};
