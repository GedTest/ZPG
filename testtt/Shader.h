#pragma once
#include <GL/glew.h>


class Shader
{
private:
	GLuint shaderID;

public:
	Shader(GLenum shaderType, const char* source);
	virtual ~Shader();

	GLuint getID() const;
};
