#include "SceneFactory.h"
#include "../Models/tree.h"
#include "../Models/bushes.h"
#include "../Models/sphere.h"
#include "../Models/suzi_flat.h"
#include "../Models/suzi_smooth.h"
#include "../Models/gift.h"
#include "../Models/plain.h"



const float SceneFactory::trianglePoints[] = {
	1.0f,  1.0f, 0.0f, 1, 1, 0,
	0.0f,  -1.0f, 0.0f, 1, 1, 0,
	-1.0f,  1.0f, 0.0f, 1, 1, 0
};

const float SceneFactory::groundPoints[] = {
	-0.25f,  0.25f, 0.0f, 0.12549f, 0.48235f, 0.05882f,
	0.25f, 0.25f, 0.0f, 0.12549f, 0.48235f, 0.05882f,
	-0.25f, -0.25f, 0.0f, 0.12549f, 0.48235f, 0.05882f,

	-0.25f, -0.25f, 0.0f, 0.12549f, 0.48235f, 0.05882f,
	0.25f, -0.25f, 0.0f, 0.12549f, 0.48235f, 0.05882f,
	0.25f, 0.25f, 0.0f, 0.12549f, 0.48235f, 0.05882f,
};

Scene* SceneFactory::createScene1Triangle()
{
	Scene* scene = new Scene();
	PointLight* light = new PointLight();

	ShaderProgram* triangleProgram = new ShaderProgram(ShaderProgram::ShaderType::CONSTANT, &scene->camera, light);
	scene->addShaderProgram(triangleProgram);

	ZPG::Model* triangleModel = new ZPG::Model(trianglePoints, sizeof(trianglePoints));

	DrawableObject* triangle = new DrawableObject(triangleProgram, triangleModel, 0, 3);
	triangle->move(glm::vec3(0, 0, 0));
	scene->addDrawableObject(triangle);

	return scene;
}

Scene* SceneFactory::createSceneDifferentLights()
{
	Scene* scene = new Scene();
	glm::vec3 lightColor = glm::vec3(1, 0, 0);
	PointLight* light = new PointLight(glm::vec3(3, 0, 8));


	ShaderProgram* constantLightShader = new ShaderProgram(ShaderProgram::ShaderType::CONSTANT, &scene->camera, light);
	scene->addShaderProgram(constantLightShader);
	ShaderProgram* lambertLightShader = new ShaderProgram(ShaderProgram::ShaderType::LAMBERT, &scene->camera, light);
	scene->addShaderProgram(lambertLightShader);
	ShaderProgram* phongLightShader = new ShaderProgram(ShaderProgram::ShaderType::PHONG, &scene->camera, light);
	scene->addShaderProgram(phongLightShader);
	ShaderProgram* blinnLightShader = new ShaderProgram(ShaderProgram::ShaderType::BLINN, &scene->camera, light);
	scene->addShaderProgram(blinnLightShader);



	ZPG::Model* bushModel = new ZPG::Model(bushes, sizeof(bushes));
	ZPG::Model* suziFlatModel = new ZPG::Model(suziFlat, sizeof(suziFlat));
	ZPG::Model* giftModel = new ZPG::Model(gift, sizeof(gift));
	ZPG::Model* sphereModel = new ZPG::Model(sphere, sizeof(sphere));
	
	int bushVertexCount = sizeof(bushes) / sizeof(float) / 6;
	DrawableObject* bushObject = new DrawableObject(constantLightShader, bushModel, 0, bushVertexCount, glm::vec3(1, 0, 0));
	scene->addDrawableObject(bushObject);
	bushObject->move(glm::vec3(0, 0, 0));
	bushObject->scale(glm::vec3(4, 4, 4));

	int suziVertexCount = sizeof(suziFlat) / sizeof(float) / 6;
	DrawableObject* suziFlatObject = new DrawableObject(lambertLightShader, suziFlatModel, 0, suziVertexCount, glm::vec3(0, 1, 0));
	scene->addDrawableObject(suziFlatObject);
	suziFlatObject->move(glm::vec3(2, 0, 0));

	int giftVertexCount = sizeof(gift) / sizeof(float) / 6;
	DrawableObject* giftObject = new DrawableObject(phongLightShader, giftModel, 0, giftVertexCount, glm::vec3(0, 0, 1));
	scene->addDrawableObject(giftObject);
	giftObject->move(glm::vec3(4, 0, 0));
	giftObject->scale(glm::vec3(5, 5, 5));

	int sphereVertexCount = sizeof(sphere) / sizeof(float) / 6;
	DrawableObject* sphereObject = new DrawableObject(blinnLightShader, sphereModel, 0, sphereVertexCount, glm::vec3(1, 1, 0));
	scene->addDrawableObject(sphereObject);
	sphereObject->move(glm::vec3(6, 0, 0));


	return scene;
}

Scene* SceneFactory::createScene4Spheres()
{
	Scene* scene = new Scene();
	PointLight* light = new PointLight();

	ShaderProgram* phongLightShader = new ShaderProgram(ShaderProgram::ShaderType::PHONG, &scene->camera, light);
	// if I want to have object with different color, I need to have new separate shader
	// object color is connected with shader, if I create one object with different color
	// it will change color in that shader pointer
	//, glm::vec3(1, 1, 0)
	//ShaderProgram* abc = new ShaderProgram(ShaderProgram::ShaderType::PHONG, &scene->camera, light);
	scene->addShaderProgram(phongLightShader);
	
	ZPG::Model* sphereModel = new ZPG::Model(sphere, sizeof(sphere));


	DrawableObject* sphere1 = new DrawableObject(phongLightShader, sphereModel, 0, sizeof(sphere) / sizeof(float) / 6);
	scene->addDrawableObject(sphere1);
	sphere1->move(glm::vec3(3, 0, 0));

	DrawableObject* sphere2 = new DrawableObject(phongLightShader, sphereModel, 0, sizeof(sphere) / sizeof(float) / 6);
	scene->addDrawableObject(sphere2);
	sphere2->move(glm::vec3(-3, 0, 0));

	DrawableObject* sphere3 = new DrawableObject(phongLightShader, sphereModel, 0, sizeof(sphere) / sizeof(float) / 6);
	scene->addDrawableObject(sphere3);
	sphere3->move(glm::vec3(0, 3, 0));

	DrawableObject* sphere4 = new DrawableObject(phongLightShader, sphereModel, 0, sizeof(sphere) / sizeof(float) / 6);
	scene->addDrawableObject(sphere4);
	sphere4->move(glm::vec3(0, -3, 0));

	
	return scene;
}

Scene* SceneFactory::createSceneForest() {
	Scene* scene = new Scene();
	PointLight* light = new PointLight(glm::vec3(0.f, 100.f, 0.f));

	ShaderProgram* shaderProgram = new ShaderProgram(ShaderProgram::ShaderType::PHONG, &scene->camera, light);

	ZPG::Model* treeModel = new ZPG::Model(tree, sizeof(tree));
	ZPG::Model* bushModel = new ZPG::Model(bushes, sizeof(bushes));

	ShaderProgram* squareProgram = new ShaderProgram(ShaderProgram::ShaderType::LAMBERT, &scene->camera, light);
	scene->addShaderProgram(squareProgram);

	ZPG::Model* squareModel = new ZPG::Model(groundPoints, sizeof(groundPoints));
	DrawableObject* ground = new DrawableObject(squareProgram, squareModel, 0, 6, glm::vec3(0,0,1));
	scene->addDrawableObject(ground);

	//order important
	//ground->move(glm::vec3(500, 0, 0));
	ground->rotate(90.f, glm::vec3(1, 0, 0));
	ground->scale(glm::vec3(10000, 10000, 1));

	for (int i = 0; i < 500; i++)
	{
		createTreeModel(scene, shaderProgram, treeModel);
		createBushModel(scene, shaderProgram, bushModel);
	}

	return scene;
}

void SceneFactory::createTreeModel(Scene* scene, ShaderProgram* shaderProgram, ZPG::Model* model) {
	scene->addShaderProgram(shaderProgram);

	float red = 0.1f + (rand() / (RAND_MAX * 1.0f)) * 0.5f;
	float green = 0.5f + (rand() / (RAND_MAX * 1.0f)) * 0.3f;
	float blue = 0.1f + (rand() / (RAND_MAX * 1.0f)) * 0.15f;

	int vertexCount = sizeof(tree) / sizeof(float) / 6;
	DrawableObject* treeObject = new DrawableObject(shaderProgram, model, 0, vertexCount, glm::vec3(red, green, blue));

	treeObject->randomTransform();
	
	scene->addDrawableObject(treeObject);
	return;
}

void SceneFactory::createBushModel(Scene* scene, ShaderProgram* shaderProgram, ZPG::Model* model) {
	scene->addShaderProgram(shaderProgram);

	float red = 0.1f + (rand() / (RAND_MAX * 1.0f)) * 0.5f;
	float green = 0.5f + (rand() / (RAND_MAX * 1.0f)) * 0.3f;
	float blue = 0.1f + (rand() / (RAND_MAX * 1.0f)) * 0.15f;

	int vertexCount = sizeof(bushes) / sizeof(float) / 6;
	DrawableObject* bushObject = new DrawableObject(shaderProgram, model, 0, vertexCount, glm::vec3(red, green, blue));

	bushObject->randomTransform();

	scene->addDrawableObject(bushObject);
	return;
}
