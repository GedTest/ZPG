#include "ShaderProgram.h"
#include <stdio.h>
#include <stdlib.h>
#define RED_COLOR     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"
void ShaderProgram::draw() const
{
	glUseProgram(this->programID);
}
ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(this->programID);
}
ShaderProgram::ShaderProgram(const char* vertex, const char* fragment)
{
	// vertex
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderID, 1, &vertex, nullptr);
	glCompileShader(vertexShaderID);
	// fragment
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderID, 1, &fragment, nullptr);
	glCompileShader(fragmentShaderID);
	this->programID = glCreateProgram();
	glAttachShader(this->programID, vertexShaderID);
	glAttachShader(this->programID, fragmentShaderID);
	glLinkProgram(this->programID);

	if (this->checkShaderLinking() == false)
	{
		exit(EXIT_FAILURE);
	}
}
bool ShaderProgram::checkShaderLinking()
{
	GLint status;
	glGetProgramiv(this->programID, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->programID, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, RED_COLOR "Shader linking failed: %s" COLOR_RESET "\n", strInfoLog);
		delete[] strInfoLog;
		return false;
	}
	return true;
}