#include "SceneFactory.h"
#include "Firefly.h"
#include "../Models/tree.h"
#include "../Models/bushes.h"
#include "../Models/sphere.h"
#include "../Models/suzi_flat.h"
#include "../Models/suzi_smooth.h"
#include "../Models/gift.h"
#include "../Models/plain.h"

#include "Scale.h"
#include "DynamicRotation.h"
#include "TexturedModel.h"
#include "Texture.h"



#include "ModelFactory.h"


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

const float groundPointsUV[] = {
	// Positions           // Colors (RGB)         // UVs
	-0.25f,  0.25f, 0.0f,   0.12549f, 0.48235f, 0.05882f,   0.0f, 1.0f, // Top-left
	 0.25f,  0.25f, 0.0f,   0.12549f, 0.48235f, 0.05882f,   1.0f, 1.0f, // Top-right
	-0.25f, -0.25f, 0.0f,   0.12549f, 0.48235f, 0.05882f,   0.0f, 0.0f, // Bottom-left

	-0.25f, -0.25f, 0.0f,   0.12549f, 0.48235f, 0.05882f,   0.0f, 0.0f, // Bottom-left
	 0.25f, -0.25f, 0.0f,   0.12549f, 0.48235f, 0.05882f,   1.0f, 0.0f, // Bottom-right
	 0.25f,  0.25f, 0.0f,   0.12549f, 0.48235f, 0.05882f,   1.0f, 1.0f  // Top-right
};


Scene* SceneFactory::createScene1Triangle()
{
	Scene* scene = new Scene();
	Light* light = Light::createPointLight();

	ShaderProgram* triangleProgram = new ShaderProgram(ShaderProgram::ShaderType::CONSTANT, &scene->camera);
	triangleProgram->addLight(light);
	scene->addShaderProgram(triangleProgram);

	Material* material = new Material();
	ZPG::Model* triangleModel = new ZPG::Model(trianglePoints, sizeof(trianglePoints), material);

	DrawableObject* triangle = new DrawableObject(triangleProgram, triangleModel);
	triangle->move(glm::vec3(0, 0, 0));
	scene->addDrawableObject(triangle);

	return scene;
}

Scene* SceneFactory::createSceneDifferentLights()
{
	Scene* scene = new Scene();
	glm::vec3 lightColor = glm::vec3(1, 0, 0);
	Light* light = Light::createDirectionalLight(glm::vec3(3, 0, -8));


	ShaderProgram* constantLightShader = new ShaderProgram(ShaderProgram::ShaderType::CONSTANT, &scene->camera);
	constantLightShader->addLight(light);
	scene->addShaderProgram(constantLightShader);
	ShaderProgram* lambertLightShader = new ShaderProgram(ShaderProgram::ShaderType::LAMBERT, &scene->camera);
	lambertLightShader->addLight(light);
	scene->addShaderProgram(lambertLightShader);
	ShaderProgram* phongLightShader = new ShaderProgram(ShaderProgram::ShaderType::PHONG, &scene->camera);
	phongLightShader->addLight(light);
	scene->addShaderProgram(phongLightShader);
	ShaderProgram* blinnLightShader = new ShaderProgram(ShaderProgram::ShaderType::BLINN, &scene->camera);
	blinnLightShader->addLight(light);
	scene->addShaderProgram(blinnLightShader);



	Material* bushMaterial = new Material();
	ZPG::Model* bushModel = new ZPG::Model(bushes, sizeof(bushes), bushMaterial);

	Material* suziFlatMaterial = new Material();
	ZPG::Model* suziFlatModel = new ZPG::Model(suziFlat, sizeof(suziFlat), suziFlatMaterial);

	Material* giftMaterial = new Material();
	ZPG::Model* giftModel = new ZPG::Model(gift, sizeof(gift), giftMaterial);

	Material* sphereMaterial = new Material();
	ZPG::Model* sphereModel = new ZPG::Model(sphere, sizeof(sphere), sphereMaterial);
	
	int bushVertexCount = sizeof(bushes) / sizeof(float) / 6;
	DrawableObject* bushObject = new DrawableObject(constantLightShader, bushModel, glm::vec3(1, 0, 0));
	scene->addDrawableObject(bushObject);
	bushObject->move(glm::vec3(0, 0, 0));
	bushObject->scale(glm::vec3(4, 4, 4));

	// test transform composition
	/*bushObject->move(glm::vec3(-10, 0, 0));		// T1
	bushObject->rotate(90, glm::vec3(1, 0, 0));		// R1
	bushObject->move(glm::vec3(10, 0, 0));			// T2
	//bushObject->rotateAroundPoint(new Rotation(90, glm::vec3(1, 0, 0)), glm::vec3(10, 0, 0));
	bushObject->move(glm::vec3(0, 5, 0));			// T3
	bushObject->scale(glm::vec3(4, 4, 4));*/		// S1

	int suziVertexCount = sizeof(suziFlat) / sizeof(float) / 6;
	DrawableObject* suziFlatObject = new DrawableObject(lambertLightShader, suziFlatModel, glm::vec3(0, 1, 0));
	scene->addDrawableObject(suziFlatObject);
	suziFlatObject->move(glm::vec3(2, 0, 0));

	int giftVertexCount = sizeof(gift) / sizeof(float) / 6;
	DrawableObject* giftObject = new DrawableObject(phongLightShader, giftModel, glm::vec3(0, 0, 1));
	scene->addDrawableObject(giftObject);
	giftObject->move(glm::vec3(4, 0, 0));
	giftObject->scale(glm::vec3(5, 5, 5));

	DynamicRotation* selfRotation = new DynamicRotation(0, glm::vec3(0, 1, 0), 25.0f);
	giftObject->rotate(selfRotation);

	int sphereVertexCount = sizeof(sphere) / sizeof(float) / 6;
	DrawableObject* sphereObject = new DrawableObject(blinnLightShader, sphereModel, glm::vec3(1, 1, 0));
	scene->addDrawableObject(sphereObject);
	sphereObject->move(glm::vec3(6, 0, 0));


	return scene;
}

Scene* SceneFactory::createScene4Spheres()
{
	Scene* scene = new Scene();
	Light* light = Light::createPointLight();

	ShaderProgram* phongLightShader = new ShaderProgram(ShaderProgram::ShaderType::PHONG, &scene->camera);
	phongLightShader->addLight(light);
	scene->addShaderProgram(phongLightShader);
	
	Material* sphereMaterial = new Material();
	ZPG::Model* sphereModel = new ZPG::Model(sphere, sizeof(sphere), sphereMaterial);


	DrawableObject* sphere1 = new DrawableObject(phongLightShader, sphereModel);
	scene->addDrawableObject(sphere1);
	sphere1->move(glm::vec3(3, 0, 0));

	DrawableObject* sphere2 = new DrawableObject(phongLightShader, sphereModel);
	scene->addDrawableObject(sphere2);
	sphere2->move(glm::vec3(-3, 0, 0));

	DrawableObject* sphere3 = new DrawableObject(phongLightShader, sphereModel);
	scene->addDrawableObject(sphere3);
	sphere3->move(glm::vec3(0, 3, 0));

	DrawableObject* sphere4 = new DrawableObject(phongLightShader, sphereModel);
	scene->addDrawableObject(sphere4);
	sphere4->move(glm::vec3(0, -3, 0));
	
	return scene;
}

Scene* SceneFactory::createSceneForest() {
	Scene* scene = new Scene();

	Light* light = Light::createPointLight(glm::vec3(0.f, 100.f, 0.f), glm::vec3(1.0f, 1.0f, 1.0f));


	ShaderProgram* shaderProgram = new ShaderProgram(ShaderProgram::ShaderType::PHONG, &scene->camera);
	shaderProgram->addLight(light);
	scene->addShaderProgram(shaderProgram);

	ShaderProgram* squareProgram = new ShaderProgram(ShaderProgram::ShaderType::LAMBERT, &scene->camera, true);
	squareProgram->addLight(light);
	scene->addShaderProgram(squareProgram);


	Material* squareMaterial = new Material(glm::vec3(1.0f, 1.0f, 1.0f));
	AbstractModel* squareTexturedModel = ModelFactory::createTexturedModel(groundPointsUV, sizeof(groundPointsUV), squareMaterial, "../Textures/grass.png");
	DrawableObject* ground = new DrawableObject(squareProgram, squareTexturedModel, glm::vec3(0, 0.5f, 0));
	scene->addDrawableObject(ground);

	ground->rotate(90.f, glm::vec3(1, 0, 0));
	ground->scale(glm::vec3(10000, 10000, 1));
	squareProgram->setTilingFactor(glm::vec2(10000/2, 10000/2));


	// swapping, removing altering transformations
	/*
	ground->move(glm::vec3(10000, 10000, 1));
	ground->transform->removeTransform(2);
	Scale* secondTranslation = dynamic_cast<Scale*>(ground->transform->getTransformAt(1));
	secondTranslation->setScale(glm::vec3(10, 10, 1));
	ground->transform->swapTransforms(0, 1);
	ground->transform->swapTransforms(0, 1);
	secondTranslation->setScale(glm::vec3(10000, 10000, 1));
	*/

	Material* bushMaterial = new Material();
	ZPG::Model* bushModel = new ZPG::Model(bushes, sizeof(bushes), bushMaterial);

	// different materials
	std::vector<Material*> treeMaterials;
	float delta = 0.03f;
	glm::vec3 baseReflectance(0.1f, 0.1f, 0.1f);
	for (int i = 0; i < 10; i++) {
		glm::vec3 reflectance = baseReflectance + (glm::vec3(1.0f) * (i * delta));
		Material* material = new Material(reflectance, pow(i, 2));
		treeMaterials.push_back(material);
	}

	std::vector<ZPG::Model*> treeModels;
	for (Material* material : treeMaterials) {
		ZPG::Model* treeModel = new ZPG::Model(tree, sizeof(tree), material);
		treeModels.push_back(treeModel);
	}
	// different materials

	for (int i = 0; i < 500; i++) {
		int materialIndex = (i / 10) % treeMaterials.size();
		ZPG::Model* currentTreeModel = treeModels[materialIndex];

		createTreeModel(scene, shaderProgram, currentTreeModel);
		createBushModel(scene, shaderProgram, bushModel);
	}

	vector<string> skyboxFaces = {
		"../Textures/posx.jpg", "../Textures/negx.jpg",
		"../Textures/posy.jpg", "../Textures/negy.jpg",
		"../Textures/posz.jpg", "../Textures/negz.jpg"
	};

	scene->addSkybox(skyboxFaces);

	return scene;
}

Scene* SceneFactory::createSceneNightForest() {
	Scene* scene = new Scene();

	Light* light = Light::createPointLight(glm::vec3(0.f, 100.f, 0.f), glm::vec3(0.3f, 0.3f, 0.3f), 1.0f, 0.0005f, 0.00005f);

	Light* spotlight = Light::createSpotLight(
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, -1),
		glm::vec3(0.0f, 1.0f, 1.0f),
		1.0f,
		0.09f,
		0.032f,
		7.0f
	);
	scene->addFlashlight(spotlight);


	ShaderProgram* shaderProgram = new ShaderProgram(ShaderProgram::ShaderType::PHONG, &scene->camera);
	shaderProgram->addLight(light);
	scene->addShaderProgram(shaderProgram);

	ShaderProgram* squareProgram = new ShaderProgram(ShaderProgram::ShaderType::LAMBERT, &scene->camera);
	squareProgram->addLight(light);
	scene->addShaderProgram(squareProgram);

	Material* squareMaterial = new Material();
	ZPG::Model* squareModel = new ZPG::Model(groundPoints, sizeof(groundPoints), squareMaterial);
	DrawableObject* ground = new DrawableObject(squareProgram, squareModel, glm::vec3(0, 0.5, 0));
	scene->addDrawableObject(ground);

	//order important
	//ground->move(glm::vec3(500, 0, 0));
	ground->rotate(90.f, glm::vec3(1, 0, 0));
	ground->scale(glm::vec3(10000, 10000, 1));

	Material* treeMaterial = new Material();
	ZPG::Model* treeModel = new ZPG::Model(tree, sizeof(tree), treeMaterial);
	Material* bushMaterial = new Material();
	ZPG::Model* bushModel = new ZPG::Model(bushes, sizeof(bushes), bushMaterial);

	for (int i = 0; i < 400; i++) {
		createTreeModel(scene, shaderProgram, treeModel);
		createBushModel(scene, shaderProgram, bushModel);
	}

	Material* sphereMaterial = new Material();
	ZPG::Model* sphereModel = new ZPG::Model(sphere, sizeof(sphere), sphereMaterial);
	for (int i = 0; i < 98; i++) {
		Firefly* firefly = new Firefly(shaderProgram, sphereModel, glm::vec3(i, 0.2f, i), glm::vec3(0.8f, 0.8f, 0.2f));
		scene->addFirefly(firefly);
	}

	return scene;
}

void SceneFactory::createTreeModel(Scene* scene, ShaderProgram* shaderProgram, ZPG::Model* model) {
	float red = 0.1f + (rand() / (RAND_MAX * 1.0f)) * 0.5f;
	float green = 0.5f + (rand() / (RAND_MAX * 1.0f)) * 0.3f;
	float blue = 0.1f + (rand() / (RAND_MAX * 1.0f)) * 0.15f;

	int vertexCount = sizeof(tree) / sizeof(float) / 6;
	DrawableObject* treeObject = new DrawableObject(shaderProgram, model, glm::vec3(red, green, blue));

	treeObject->randomTransform();
	
	scene->addDrawableObject(treeObject);
	return;
}

void SceneFactory::createBushModel(Scene* scene, ShaderProgram* shaderProgram, ZPG::Model* model) {
	float red = 0.1f + (rand() / (RAND_MAX * 1.0f)) * 0.5f;
	float green = 0.5f + (rand() / (RAND_MAX * 1.0f)) * 0.3f;
	float blue = 0.1f + (rand() / (RAND_MAX * 1.0f)) * 0.15f;

	int vertexCount = sizeof(bushes) / sizeof(float) / 6;
	DrawableObject* bushObject = new DrawableObject(shaderProgram, model, glm::vec3(red, green, blue));

	bushObject->randomTransform();

	scene->addDrawableObject(bushObject);
	return;
}

Scene* SceneFactory::createSceneSolarSystem()
{
	Scene* scene = new Scene();
	Light* light = Light::createPointLight();

	ShaderProgram* phongLightShader = new ShaderProgram(ShaderProgram::ShaderType::PHONG, &scene->camera);
	phongLightShader->addLight(light);
	scene->addShaderProgram(phongLightShader);

	Material* suziFlatMaterial = new Material();
	ZPG::Model* suziFlatModel = new ZPG::Model(suziFlat, sizeof(suziFlat), suziFlatMaterial);
	int suziVertexCount = sizeof(suziFlat) / sizeof(float) / 6;


	/* Sun */
	DrawableObject* sun = new DrawableObject(phongLightShader, suziFlatModel, glm::vec3(1, 1, 0));
	scene->addDrawableObject(sun);
	sun->scale(glm::vec3(2, 2, 2));
	sun->rotate(10.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	float sunRotationSpeed = 5.0f;
	DynamicRotation* sunSelfRotation = new DynamicRotation(0, glm::vec3(0, 1, 0), sunRotationSpeed);
	sun->rotate(sunSelfRotation);


	/* Earth */
	DrawableObject* earth = new DrawableObject(phongLightShader, suziFlatModel, glm::vec3(0, 0, 1));
	scene->addDrawableObject(earth);
	earth->scale(glm::vec3(0.5, 0.5, 0.5));
	
	glm::vec3 objectPosition(10, 0, 0);
	earth->move(objectPosition);

	float rotationSpeed = 15.0f;
	DynamicRotation* rotation = new DynamicRotation(0, glm::vec3(0, 1, 0), rotationSpeed);

	float earthSelfRotationSpeed = 100.0f;
	DynamicRotation* selfRotation = new DynamicRotation(0, glm::vec3(0, 1, 0), earthSelfRotationSpeed);
	
	earth->rotateAroundPoint(rotation, objectPosition);
	earth->rotate(selfRotation);

	// tilt earth
	earth->rotate(23.5f, glm::vec3(1, 0, 0));
	


	return scene;
}

Scene* SceneFactory::createSceneLoadedModels()
{
	Scene* scene = new Scene();
	Light* light = Light::createPointLight();


	ShaderProgram* phongLightShader = new ShaderProgram(ShaderProgram::ShaderType::PHONG, &scene->camera);
	phongLightShader->addLight(light);
	scene->addShaderProgram(phongLightShader);
	
	// simple model
	AbstractModel* simpleModel = ModelFactory::createModel(gift, sizeof(gift), new Material());
	DrawableObject* simpleObject = new DrawableObject(phongLightShader, simpleModel, glm::vec3(0, 1, 0));
	simpleObject->move(glm::vec3(1, 0, -2));
	scene->addDrawableObject(simpleObject);


	// textured model
	ShaderProgram* squareProgram = new ShaderProgram(ShaderProgram::ShaderType::LAMBERT, &scene->camera, true);
	squareProgram->addLight(light);
	scene->addShaderProgram(squareProgram);

	AbstractModel* squareTexturedModel = ModelFactory::createTexturedModel(groundPointsUV, sizeof(groundPointsUV), new Material(glm::vec3(1.0f, 1.0f, 1.0f)), "../Textures/grass.png");
	DrawableObject* ground = new DrawableObject(squareProgram, squareTexturedModel, glm::vec3(0, 1, 0));
	scene->addDrawableObject(ground);

	ground->rotate(90.f, glm::vec3(1, 0, 0));
	ground->scale(glm::vec3(10000, 10000, 1));
	squareProgram->setTilingFactor(glm::vec2(10000 / 2, 10000 / 2));


	ShaderProgram* modelLoaderShaderProgram = new ShaderProgram(ShaderProgram::ShaderType::ASSIMP, &scene->camera);
	scene->addShaderProgram(modelLoaderShaderProgram);

	AbstractModel* assimpModel = ModelFactory::createAssimpModel("../Models/house.obj", new Material(), "../Models/house.png");
	DrawableObject* assimpObject = new DrawableObject(modelLoaderShaderProgram, assimpModel, glm::vec3(0,0 ,1));
	scene->addDrawableObject(assimpObject);


	ShaderProgram* modelLoaderShaderProgram2 = new ShaderProgram(ShaderProgram::ShaderType::ASSIMP, &scene->camera);
	scene->addShaderProgram(modelLoaderShaderProgram2);

	AbstractModel* loginModel = ModelFactory::createAssimpModel("../Models/ZWI0015.obj", new Material());
	DrawableObject* loginObject = new DrawableObject(modelLoaderShaderProgram2, loginModel, glm::vec3(0, 0, 0.7));
	loginObject->move(glm::vec3(-2.5, 7, 10));
	scene->addDrawableObject(loginObject);






	ShaderProgram* modelLoaderShaderProgram3 = new ShaderProgram(ShaderProgram::ShaderType::ASSIMP, &scene->camera);
	scene->addShaderProgram(modelLoaderShaderProgram3);

	AbstractModel* snailModel = ModelFactory::createAssimpModel("../Models/Unicorn/Unicorn.obj", new Material());
	DrawableObject* snailObject = new DrawableObject(modelLoaderShaderProgram3, snailModel, glm::vec3(1, 0, 0.564));
	snailObject->move(glm::vec3(0, 4.5, 10));
	snailObject->scale(glm::vec3(0.1, 0.1, 0.1));
	snailObject->rotate(270, glm::vec3(1, 0, 0));
	scene->addDrawableObject(snailObject);

	return scene;
}