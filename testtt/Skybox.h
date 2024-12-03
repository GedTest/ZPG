#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Observer.h"
#include "Camera.h"
#include "CubemapTexture.h"
#include "ShaderProgram.h"
#include "DrawableObject.h"
using std::vector;
using std::string;


class Skybox : public Observer {
private:
	DrawableObject* drawableObject;
	Camera* camera;
	ShaderProgram* shaderProgram;
	CubemapTexture* texture;
	bool followCamera;
	
public:
	Skybox(const vector<string>& faces, Camera* camera);
	~Skybox();

	void draw();
	void update() override;
	void toggleFollowCamera();
};
