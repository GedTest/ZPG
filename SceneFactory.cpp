#include "SceneFactory.h"
#include "../Models/tree.h"
#include "../Models/bushes.h"
#include "../Models/sphere.h"
#include "../Models/suzi_flat.h"
#include "../Models/suzi_smooth.h"
#include "../Models/gift.h"
#include "../Models/plain.h"
#include <iostream>


const float SceneFactory::trianglePoints[] = {
	-0.5f,  0.25f, 0.0f, 1, 1, 0,
	-0.25f, 0.f, 0.0f, 1, 1, 0,
	-0.25f, -0.5f, 0.0f, 1, 1, 0,
};

const float SceneFactory::squarePoints[] = {
	-0.25f,  0.5f, 0.0f, 0, 0, 1,
	0.25f, 0.f, 0.0f, 0, 0, 1,
	-0.25f, 0.f, 0.0f, 0, 0, 1,

	// additional vertices for square out of 2 triangles
	-0.25f,  0.5f, 0.0f, 0, 0, 1,
	0.25f, 0.f, 0.0f, 0, 0, 1,
	0.25f, 0.5f, 0.0f, 0, 0, 1,
};

const float SceneFactory::roofPoints[] = {
	0.f,  0.5f, 0.0f, 1, 0, 0,
	0.25f, 0.f, 0.0f, 1, 0, 0,
	-0.25f, 0.f, 0.0f, 1, 0, 0,
};

const float SceneFactory::wallPoints[] = {
	-0.25f,  0.f, 0.0f, 0, 1, 0,
	0.25f, 0.f, 0.0f, 0, 1, 0,
	-0.25f, -0.5f, 0.0f, 0, 1, 0,

	-0.25f, -0.5f, 0.0f, 0, 1, 0,
	0.25f, -0.5f, 0.0f, 0, 1, 0,
	0.25f, 0.f, 0.0f, 0, 1, 0,
};


const char* SceneFactory::triangleVertexShader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 normal;"
"uniform mat4 modelMatrix;"
"out vec3 color;"
"void main() {"
"     color = normal;"
"     gl_Position = modelMatrix * vec4(vp, 1.0);"
"}";

const char* SceneFactory::squareVertexShader =
"#version 330\n"
"layout(location=0) in vec3 vp;"
"layout(location=1) in vec3 normal;"
"uniform mat4 modelMatrix;"
"out vec3 color;"
"void main() {"
"     color = normal;"
"     gl_Position = modelMatrix * vec4(vp, 1.0);"
"}";

const char* SceneFactory::fragmentShader =
"#version 330\n"
"in vec3 color;"
"out vec4 frag_colour;"
"void main() {"
"    frag_colour = vec4(color, 1.0);"
"}";


ShaderProgram* SceneFactory::createShaderProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
	VertexShader vertexShader(vertexShaderSource);
	FragmentShader fragmentShader(fragmentShaderSource);
	return new ShaderProgram(vertexShader, fragmentShader);
}

Scene* SceneFactory::createSceneA()
{
	Scene* scene = new Scene();

	// Create shader programs
	ShaderProgram* triangleProgram = createShaderProgram(triangleVertexShader, fragmentShader);
	scene->addShaderProgram("triangle", triangleProgram);

	ShaderProgram* squareProgram = createShaderProgram(squareVertexShader, fragmentShader);
	scene->addShaderProgram("square", squareProgram);

	ZPG::Model* triangleModel = new ZPG::Model(trianglePoints, sizeof(trianglePoints));
	ZPG::Model* squareModel = new ZPG::Model(squarePoints, sizeof(squarePoints));

	// Create drawable objects
	scene->addDrawableObject(new DrawableObject(triangleProgram, triangleModel, 0, 3));

	DrawableObject* triangle2 = new DrawableObject(triangleProgram, triangleModel, 0, 3);
	triangle2->scale(glm::vec3(-1, 1, 1));

	scene->addDrawableObject(triangle2);

	scene->addDrawableObject(new DrawableObject(squareProgram, squareModel, 0, 6));

	return scene;
}

Scene* SceneFactory::createSceneHouse()
{
	Scene* scene = new Scene();

	// Create shader programs
	ShaderProgram* triangleProgram = createShaderProgram(triangleVertexShader, fragmentShader);
	scene->addShaderProgram("triangle", triangleProgram);

	ShaderProgram* squareProgram = createShaderProgram(squareVertexShader, fragmentShader);
	scene->addShaderProgram("square", squareProgram);

	// Create drawable objects
	ZPG::Model* triangleModel = new ZPG::Model(roofPoints, sizeof(roofPoints));
	scene->addDrawableObject(new DrawableObject(triangleProgram, triangleModel, 0, 3));

	ZPG::Model* squareModel = new ZPG::Model(wallPoints, sizeof(wallPoints));
	scene->addDrawableObject(new DrawableObject(squareProgram, squareModel, 0, 6));

	return scene;
}

Scene* SceneFactory::createSceneForest() {
	Scene* scene = new Scene();

	ShaderProgram* shaderProgram = createShaderProgram(triangleVertexShader, fragmentShader);

	ZPG::Model* treeModel = new ZPG::Model(tree, sizeof(tree));
	ZPG::Model* bushModel = new ZPG::Model(bushes, sizeof(bushes));

	for (int i = 0; i < 10; i++)
	{
		createTreeModel(scene, shaderProgram, treeModel);
		createBushModel(scene, shaderProgram, bushModel);
	}

	return scene;
}

void SceneFactory::createTreeModel(Scene* scene, ShaderProgram* shaderProgram, ZPG::Model* model) {
	scene->addShaderProgram("tree", shaderProgram);

	int vertexCount = sizeof(tree) / sizeof(float) / 6;
	DrawableObject* treeObject = new DrawableObject(shaderProgram, model, 0, vertexCount);

	treeObject->randomTransform();
	
	scene->addDrawableObject(treeObject);
	return;
}

void SceneFactory::createBushModel(Scene* scene, ShaderProgram* shaderProgram, ZPG::Model* model) {
	scene->addShaderProgram("bush", shaderProgram);

	int vertexCount = sizeof(bushes) / sizeof(float) / 6;
	DrawableObject* bushObject = new DrawableObject(shaderProgram, model, 0, vertexCount);

	bushObject->randomTransform();

	scene->addDrawableObject(bushObject);
	return;
}
