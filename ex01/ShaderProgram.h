#pragma once
#include <GL/glew.h>
#include "VertexArrayObject.h"
#include "VertexShader.h"
#include "FragmentShader.h"
class ShaderProgram
{
public:
	ShaderProgram(const char* vertex, const char* fragment);
	void draw() const;
	~ShaderProgram();
private:
	GLuint programID;
	bool checkShaderLinking();
};