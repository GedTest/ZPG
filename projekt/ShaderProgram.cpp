#include "ShaderProgram.h"
#include "Camera.h"
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

GLuint ShaderProgram::getShaderVariable(const char* name) {
	GLuint location = glGetUniformLocation(this->programID, name);
	if (location == -1) {
		cerr << RED_COLOR << "ERROR shader variable not found: " << name << COLOR_RESET << endl;
		exit(EXIT_FAILURE);
	}
	return location;
}

const char* ShaderProgram::getShaderPath(ShaderType type) {
	switch (type) {
		case ShaderType::CONSTANT:
			return "./constant_fragment.glsl";
		case ShaderType::LAMBERT:
			return "./lambert_fragment.glsl";
		case ShaderType::PHONG:
			return "./phong_fragment.glsl";
		case ShaderType::BLINN:
			return "./blinn_fragment.glsl";
	}
}

void ShaderProgram::setUniformMatrix(const char* name, const glm::mat4& matrix) {
	GLuint location = this->getShaderVariable(name);
	
					// location, count, transpose, *value
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	return;
}

void ShaderProgram::setUniformVec3(const char* name, const glm::vec3& vector) {
	GLuint location = this->getShaderVariable(name);
	
	glUniform3fv(location, 1, glm::value_ptr(vector));
	return;
}

void ShaderProgram::setUniformFloat(const char* name, float value) {
	GLuint location = this->getShaderVariable(name);

	glUniform1f(location, value);
	return;
}

ShaderProgram::ShaderProgram(ShaderType type, Camera* camera, PointLight* light)
{
	this->type = type;
	this->light = light;
	this->camera = camera;

	const char* vertexPath = "./vertex_shader.glsl";
	const char* fragmentPath = this->getShaderPath(type);


	this->shaderLoader = new ShaderLoader();
	this->programID = this->shaderLoader->loadShader(vertexPath, fragmentPath);

	if (this->checkShaderLinking() == false)
	{
		exit(EXIT_FAILURE);
	}

	this->camera->subscribe(this);
	this->light->subscribe(this);
}

void ShaderProgram::setObjectColor(const glm::vec3& color)
{
	this->setProgram();
	setUniformVec3("objectColor", color);
	return;
}

void ShaderProgram::setLightUniforms() {
	if (this->type == ShaderType::CONSTANT) { return; }

	this->setProgram();
	setUniformVec3("lightPosition", this->light->getPosition());
	setUniformVec3("lightColor", this->light->getColor());
	
	if (this->type != ShaderType::LAMBERT) {
		setUniformVec3("viewPosition", this->camera->getEye());
	}
	return;
}

ShaderProgram::~ShaderProgram()
{
	if (this->camera) {
		this->camera->unsubscribe(this);
	}
	
	this->shaderLoader->deleteShader();
	delete this->shaderLoader;
}

void ShaderProgram::setProgram()
{
	glUseProgram(this->programID);
	return;
}

void ShaderProgram::update() {
	this->setProgram();

	if (this->camera) {
		glm::mat4 view = this->camera->lookAt();
		this->setViewMatrix(view);
	}
	this->setLightUniforms();
	return;
}

void ShaderProgram::setModelMatrix(const glm::mat4& matrix)
{
	this->setUniformMatrix("modelMatrix", matrix);
	return;
}

void ShaderProgram::setViewMatrix(const glm::mat4& matrix)
{
	this->setUniformMatrix("viewMatrix", matrix);
	return;
}

void ShaderProgram::setProjectionMatrix()
{
	this->setUniformMatrix("projectionMatrix", this->camera->getProjectionMatrix());
	return;
}

void ShaderProgram::setType(ShaderType newType) {
	const char* vertexPath = "./vertex_shader.glsl";
	const char* fragmentPath = "./constant_fragment.glsl";

	switch (newType) {
	case ShaderType::CONSTANT:
		fragmentPath = "./constant_fragment.glsl";
		break;
	case ShaderType::LAMBERT:
		fragmentPath = "./lambert_fragment.glsl";
		break;
	case ShaderType::PHONG:
		fragmentPath = "./phong_fragment.glsl";
		break;
	case ShaderType::BLINN:
		fragmentPath = "./blinn_fragment.glsl";
		break;
	}


	if (this->programID != 0) {
		glDeleteProgram(this->programID);
	}

	this->programID = this->shaderLoader->loadShader(vertexPath, fragmentPath);
	this->type = newType;
	this->setProgram();
	return;
}
