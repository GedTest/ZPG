#include "BaseShader.h"
BaseShader::BaseShader(GLenum shaderType, const char* source)
{
    this->shaderID = glCreateShader(shaderType);
    glShaderSource(this->shaderID, 1, &source, nullptr);
    glCompileShader(this->shaderID);
}
BaseShader::~BaseShader()
{
    glDeleteShader(shaderID);
}
GLuint BaseShader::getID() const
{
    return shaderID;
}