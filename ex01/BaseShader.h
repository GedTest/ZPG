#pragma once
#include <GL/glew.h>
class BaseShader
{
public:
	BaseShader(GLenum shaderType, const char* source);
	virtual ~BaseShader();
	GLuint getID() const;
private:
	GLuint shaderID;
};
