#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SceneFactory.h"


class OpenGLApplication
{
private:
	GLFWwindow* window;
	std::vector<Scene*> scenes;
	int currentSceneIndex;

	void printVersionInfo();
	
	static void errorCallback(int error, const char* description) { fputs(description, stderr); }
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	OpenGLApplication(bool printInfo=false);
	~OpenGLApplication();

	void cycleScenes();
	void run();
	void switchScenes(Scene* newScene);
};
