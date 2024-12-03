#pragma once
#include "Scene.h"
#include "VertexShader.h"
#include "FragmentShader.h"
#include "Model.h"


class SceneFactory
{
private:
	static void createTreeModel(Scene* scene, ShaderProgram* shaderProgram, ZPG::Model* model);
	static void createBushModel(Scene* scene, ShaderProgram* shaderProgram, ZPG::Model* model);

	static const float trianglePoints[];
	static const float groundPoints[];

public:
	static Scene* createScene1Triangle();
	static Scene* createSceneDifferentLights();
	static Scene* createScene4Spheres();
	static Scene* createSceneForest();
	static Scene* createSceneNightForest();
	static Scene* createSceneSolarSystem();
	static Scene* createSceneLoadedModels();
};
