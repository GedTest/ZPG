#pragma once
#include <GL/glew.h>
#include "VertexArrayObject.h"
#include "VertexShader.h"
#include "FragmentShader.h"


class ShaderProgram
{
private:
	GLuint programID;

	bool checkShaderLinking();

public:
	ShaderProgram(const VertexShader& vertex, const FragmentShader& fragment);
	~ShaderProgram();

	GLuint getUniformLocation(const char* name);
	void setProgram();
};
