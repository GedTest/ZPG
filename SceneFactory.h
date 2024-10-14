#pragma once
#include "Scene.h"
#include "VertexShader.h"
#include "FragmentShader.h"


class SceneFactory
{
private:
	static ShaderProgram* createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
	static void createTreeModel(Scene* scene, ShaderProgram* shaderProgram, ZPG::Model* model);
	static void createBushModel(Scene* scene, ShaderProgram* shaderProgram, ZPG::Model* model);

	static const float trianglePoints[];
	static const float squarePoints[];
	static const float roofPoints[];
	static const float wallPoints[];

	static const char* triangleVertexShader;
	static const char* squareVertexShader;
	static const char* fragmentShader;

	static const char* treeVertexShader;

public:
	static Scene* createSceneA();
	static Scene* createSceneHouse();

	static Scene* createSceneForest();
};
