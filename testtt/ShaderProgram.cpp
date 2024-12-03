#include "ShaderProgram.h"
#include "Camera.h"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;
using std::string;

#define RED_COLOR     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"

const string TEXTURE_SUFFIX = "_texture";


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
	this->setProgram();
	GLuint location = glGetUniformLocation(this->programID, name);
	if (location == -1) {
		cerr << RED_COLOR << "ERROR shader variable not found: " << name << COLOR_RESET << endl;
		exit(EXIT_FAILURE);
	}
	
	return location;
}

void ShaderProgram::setUniformMatrix(const char* name, const glm::mat4& matrix) {
	GLuint location = this->getShaderVariable(name);
	
					// location, count, transpose, *value
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	this->resetProgram();
	return;
}

void ShaderProgram::setUniformVec3(const char* name, const glm::vec3& vector) {
	GLuint location = this->getShaderVariable(name);
	
	glUniform3fv(location, 1, glm::value_ptr(vector));
	this->resetProgram();
	return;
}

void ShaderProgram::setUniformVec2(const char* name, const glm::vec2& vector) {
	GLuint location = this->getShaderVariable(name);

	glUniform2fv(location, 1, glm::value_ptr(vector));
	this->resetProgram();
	return;
}

void ShaderProgram::setUniformFloat(const char* name, float value) {
	GLuint location = this->getShaderVariable(name);

	glUniform1f(location, value);
	this->resetProgram();
	return;
}

void ShaderProgram::setUniformInt(const char* name, int value) {
	GLuint location = this->getShaderVariable(name);

	glUniform1i(location, value);
	this->resetProgram();
	return;
}

ShaderProgram::ShaderProgram(ShaderType type, Camera* camera, bool hasTexture)
{
	this->type = type;
	this->camera = camera;
	this->hasTexture = hasTexture;
	this->shaderLoader = new ShaderLoader();
	this->setType(this->type);

	if (this->checkShaderLinking() == false)
	{
		exit(EXIT_FAILURE);
	}

	this->camera->subscribe(this);
}

void ShaderProgram::setObjectColor(const glm::vec3& color)
{
	if (this->type == ShaderType::SKYBOX) { return; }
	setUniformVec3("objectColor", color);
	return;
}

void ShaderProgram::setMaterialProperties(Material* material)
{
	if (this->type == ShaderType::SKYBOX || this->type == ShaderType::ASSIMP) { return; }
	if (this->type == ShaderType::CONSTANT) { return; }
	setUniformVec3("material.reflectance", material->reflectance);

	if (this->type != ShaderType::LAMBERT) {
		setUniformFloat("material.shininess", material->shininess);
	}
	return;
}

void ShaderProgram::setTilingFactor(glm::vec2 scale) {
	setUniformVec2("tilingFactor", scale);
	return;
}

void ShaderProgram::setLightUniforms() {
	if (this->type == ShaderType::CONSTANT || this->type == ShaderType::SKYBOX || this->type == ShaderType::ASSIMP) { return; }
	
	this->setUniformInt("numLights", static_cast<GLint>(lights.size()));

	for (int i = 0; i < lights.size(); i++) {
		char light[100];
		snprintf(light, sizeof(light), "lights[%d]", i);

		char uniformVariable[100];

		snprintf(uniformVariable, sizeof(uniformVariable), "%s.type", light);
		setUniformInt(uniformVariable, static_cast<int>(lights[i]->getType()));

		snprintf(uniformVariable, sizeof(uniformVariable), "%s.position", light);
		setUniformVec3(uniformVariable, this->lights[i]->getPosition());

		snprintf(uniformVariable, sizeof(uniformVariable), "%s.direction", light);
		setUniformVec3(uniformVariable, lights[i]->getDirection());

		snprintf(uniformVariable, sizeof(uniformVariable), "%s.color", light);
		setUniformVec3(uniformVariable, this->lights[i]->getColor());

		snprintf(uniformVariable, sizeof(uniformVariable), "%s.constantAttenuation", light);
		setUniformFloat(uniformVariable, this->lights[i]->getConstantAttenuation());

		snprintf(uniformVariable, sizeof(uniformVariable), "%s.linearAttenuation", light);
		setUniformFloat(uniformVariable, this->lights[i]->getLinearAttenuation());

		snprintf(uniformVariable, sizeof(uniformVariable), "%s.quadraticAttenuation", light);
		setUniformFloat(uniformVariable, this->lights[i]->getQuadraticAttenuation());

		snprintf(uniformVariable, sizeof(uniformVariable), "%s.cutOff", light);
		setUniformFloat(uniformVariable, lights[i]->getCutOffAngle());

		snprintf(uniformVariable, sizeof(uniformVariable), "%s.outerCutOff", light);
		setUniformFloat(uniformVariable, lights[i]->getOuterCutOffAngle());
	}
	
	if (this->type != ShaderType::LAMBERT) {
		setUniformVec3("viewPosition", this->camera->getEye());
	}

	this->resetProgram();
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

void ShaderProgram::resetProgram()
{
	glUseProgram(0);
	return;
}

void ShaderProgram::update() {
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

void ShaderProgram::setSkybox() {
	this->setUniformInt("skybox", 0);
	return;
}

void ShaderProgram::setType(ShaderType newType) {
	string vertexPath = "./vertex_shader";
	string fragmentPath = "./constant_fragment";

	
	switch (newType) {
	case ShaderType::CONSTANT:
		fragmentPath = "./constant_fragment";
		break;
	case ShaderType::LAMBERT:
		fragmentPath = "./lambert_fragment";
		break;
	case ShaderType::PHONG:
		fragmentPath = "./phong_fragment";
		break;
	case ShaderType::BLINN:
		fragmentPath = "./blinn_fragment";
		break;
	case ShaderType::SKYBOX:
		vertexPath = "./vertex_shader_skybox";
		fragmentPath = "./fragment_shader_skybox";
		break;
	case ShaderType::ASSIMP:
		vertexPath = "./vertex_shader_assimp";
		fragmentPath = "./fragment_shader_assimp";
		break;
	}

	if (this->hasTexture == true) {
		vertexPath += TEXTURE_SUFFIX;
		fragmentPath += TEXTURE_SUFFIX;
	}
	vertexPath += ".glsl";
	fragmentPath += ".glsl";


	if (this->programID != 0) {
		glDeleteProgram(this->programID);
	}

	this->programID = this->shaderLoader->loadShader(vertexPath.c_str(), fragmentPath.c_str());
	
	this->type = newType;
	this->update();

	return;
}

void ShaderProgram::setTexture(AbstractTexture* texture) {
	texture->bind();
	this->setUniformInt("textureUnitID", texture->getAssignedUnit());
	return;
}

void ShaderProgram::setUseTextureFlag(bool useTexture) {
	if (this->type != ShaderType::ASSIMP) { return; }
	this->setUniformInt("useTexture", useTexture);
	this->setObjectColor(glm::vec3(0, 0, 1));
	return;
}

void ShaderProgram::addLight(Light* light) {
	this->lights.push_back(light);
	light->subscribe(this);
	return;
}

void ShaderProgram::removeLight(Light* light) {
	if (this->lights.size() == 0) { return; }
	auto it = std::find(this->lights.begin(), this->lights.end(), light);
	if (it != this->lights.end()) {
		(*it)->unsubscribe(this);
		this->lights.erase(it);
	}
	return;
}
