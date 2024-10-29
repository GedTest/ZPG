#pragma once
#include <GL/glew.h>
#include "VertexArrayObject.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ShaderLoader.h"
#include "Observer.h"
#include "PointLight.h"


class Camera;
class ShaderProgram : public Observer
{
public:
	enum class ShaderType {
		CONSTANT,
		LAMBERT,
		PHONG,
		BLINN
	};
private:
	GLuint programID;
	Camera* camera;
	ShaderLoader* shaderLoader;
	PointLight* light;
	ShaderType type;

	bool checkShaderLinking();
	void setUniformMatrix(const char* name, const glm::mat4& matrix);
	void setUniformVec3(const char* name, const glm::vec3& vector);
	void setUniformFloat(const char* name, float value);
	GLuint getShaderVariable(const char* name);
	const char* getShaderPath(ShaderType type);

public:
	ShaderProgram(ShaderType type, Camera* camera, PointLight* light);
	~ShaderProgram() override;

	void setProgram();

	void update() override;

	void setModelMatrix(const glm::mat4& matrix);
	void setViewMatrix(const glm::mat4& matrix);
	void setProjectionMatrix();
	void setObjectColor(const glm::vec3& color);

	void setLightUniforms();
	void setType(ShaderType newType);
};
