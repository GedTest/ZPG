#include "ShaderProgram.h"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

#define RED_COLOR     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"


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
		cerr << RED_COLOR << "Shader linking failed: " << strInfoLog << COLOR_RESET << endl;

		delete[] strInfoLog;
		return false;
	}
	return true;
}

ShaderProgram::ShaderProgram(const VertexShader& vertex, const FragmentShader& fragment)
{

	this->programID = glCreateProgram();
	glAttachShader(this->programID, vertex.getID());
	glAttachShader(this->programID, fragment.getID());
	glLinkProgram(this->programID);

	
	if (this->checkShaderLinking() == false)
	{
		exit(EXIT_FAILURE);
	}
}

ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(this->programID);
}

GLuint ShaderProgram::getUniformLocation(const char* name)
{
	GLuint location = glGetUniformLocation(this->programID, name);
	if (location == -1) {
		cerr << "ERROR::SHADER::UNIFORM_LOCATION_NOT_FOUND: '" << name << endl;
		exit(EXIT_FAILURE);
	}
	return location;
}

void ShaderProgram::setProgram()
{
	glUseProgram(this->programID);
	return;
}
