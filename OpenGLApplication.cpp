#include "OpenGLApplication.h"
#include <iostream>

using std::cout;
using std::endl;


void OpenGLApplication::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		OpenGLApplication* app = static_cast<OpenGLApplication*>(glfwGetWindowUserPointer(window));
		app->cycleScenes();
	}
	return;
}

void OpenGLApplication::printVersionInfo()
{
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);

	cout << "OpenGL Version: " << glGetString(GL_VERSION) << endl
		<< "Using GLEW " << glewGetString(GLEW_VERSION) << endl
		<< "Vendor " << glGetString(GL_VENDOR) << endl
		<< "Renderer " << glGetString(GL_RENDERER) << endl
		<< "GLSL " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl
		<< "Using GLFW " << major << "." << minor << "." << revision << endl;

	return;
}

OpenGLApplication::OpenGLApplication(bool printInfo) {
	glfwSetErrorCallback(this->errorCallback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	this->window = glfwCreateWindow(800, 600, "ZPG", nullptr, nullptr);
	if (this->window == nullptr) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(this->window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	int width, height;
	glfwGetFramebufferSize(this->window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	if (printInfo == true) {
		this->printVersionInfo();
	}

	glfwSetWindowUserPointer(this->window, this);
	glfwSetKeyCallback(this->window, this->keyCallback);

	this->scenes.push_back(SceneFactory::createSceneA());
	this->scenes.push_back(SceneFactory::createSceneHouse());
	this->scenes.push_back(SceneFactory::createSceneForest());

	this->currentSceneIndex = 0;
}

OpenGLApplication::~OpenGLApplication()
{
	for (Scene* scene : this->scenes) {
		delete scene;
	}
}

void OpenGLApplication::cycleScenes() {
	if (this->scenes.empty() == false) {
		this->currentSceneIndex = (this->currentSceneIndex + 1) % this->scenes.size();
		cout << "Switched to scene " << this->currentSceneIndex << endl;
	}
	return;
}

void OpenGLApplication::run()
{
	while (!glfwWindowShouldClose(this->window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (this->scenes.empty() == false) {
			this->scenes[this->currentSceneIndex]->draw();
		}

		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(this->window);
	}

	glfwDestroyWindow(this->window);
	glfwTerminate();
	return;
}

void OpenGLApplication::switchScenes(Scene* newScene)
{
	auto iterator = std::find(this->scenes.begin(), this->scenes.end(), newScene);
	if (iterator != this->scenes.end()) {
		this->currentSceneIndex = std::distance(this->scenes.begin(), iterator);
		cout << "Switched to scene " << this->currentSceneIndex << endl;
	}
	else {
		cout << "Scene not found" << endl;
	}
	return;
}
