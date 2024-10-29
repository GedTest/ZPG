#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SceneFactory.h"


class Application
{
private:
	glm::vec2 prevPosition = glm::vec2(400.f, 300.f);

	GLFWwindow* window;
	std::vector<Scene*> scenes;
	int currentSceneIndex;

	void printVersionInfo();
	
	static void errorCallback(int error, const char* description) { fputs(description, stderr); }
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

public:
	Application(bool printInfo=false);
	~Application();

	void cycleScenes();
	void run();
};
