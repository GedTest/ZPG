#pragma once
#include <GL/glew.h>
#include "VertexArrayObject.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "ShaderLoader.h"
#include "Observer.h"
#include "Light.h"
#include "Material.h"
#include "Texture.h"


class Camera;
class ShaderProgram : public Observer
{
public:
	enum class ShaderType {
		CONSTANT,
		LAMBERT,
		PHONG,
		BLINN,
		SKYBOX,
		ASSIMP
	};

private:
	Camera* camera;
	ShaderLoader* shaderLoader;
	std::vector<Light*> lights;
	ShaderType type;
	bool hasTexture;

	bool checkShaderLinking();
	void setUniformMatrix(const char* name, const glm::mat4& matrix);
	void setUniformVec2(const char* name, const glm::vec2& vector);
	void setUniformVec3(const char* name, const glm::vec3& vector);
	void setUniformFloat(const char* name, float value);
	void setUniformInt(const char* name, int value);
	GLuint getShaderVariable(const char* name);

public:
	GLuint programID;
	ShaderProgram(ShaderType type, Camera* camera, bool hasTexture=false);
	~ShaderProgram() override;

	void setProgram();
	void resetProgram();

	void update() override;

	void setModelMatrix(const glm::mat4& matrix);
	void setViewMatrix(const glm::mat4& matrix);
	void setProjectionMatrix();
	void setObjectColor(const glm::vec3& color);
	void setMaterialProperties(Material* material);
	void setSkybox();

	void setLightUniforms();
	void setType(ShaderType newType);

	void setTexture(AbstractTexture* textureID);
	void setTilingFactor(glm::vec2 scale);
	void setUseTextureFlag(bool useTexture);

	void addLight(Light* light);
    void removeLight(Light* light);
};
