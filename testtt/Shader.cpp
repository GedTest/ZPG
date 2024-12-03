#include "Shader.h"


Shader::Shader(GLenum shaderType, const char* source)
{
    this->shaderID = glCreateShader(shaderType);
    glShaderSource(this->shaderID, 1, &source, nullptr);
    glCompileShader(this->shaderID);
}

Shader::~Shader()
{
    glDeleteShader(shaderID);
}

GLuint Shader::getID() const
{
    return shaderID;
}
