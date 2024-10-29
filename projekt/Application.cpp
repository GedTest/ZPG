#include "Application.h"
#include <iostream>

using std::cout;
using std::endl;


void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_TAB && action == GLFW_PRESS) {
		app->cycleScenes();
	}

	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		app->scenes[app->currentSceneIndex]->cycleLightShaders();
	}
	return;
}

void Application::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
	Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));

	float xoffset = xpos - app->prevPosition.x;
	float yoffset = ypos - app->prevPosition.y;

	app->prevPosition.x = xpos;
	app->prevPosition.y = ypos;

	app->scenes[app->currentSceneIndex]->camera.rotate(xoffset, yoffset, 0.5f);
}

void Application::printVersionInfo()
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

Application::Application(bool printInfo) {
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


	glfwSetCursorPosCallback(this->window, mouseCallback);
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	
	glfwSetWindowUserPointer(this->window, this);
	glfwSetKeyCallback(this->window, this->keyCallback);


	this->scenes.push_back(SceneFactory::createScene1Triangle());
	this->scenes.push_back(SceneFactory::createSceneDifferentLights());	
	this->scenes.push_back(SceneFactory::createScene4Spheres());
	this->scenes.push_back(SceneFactory::createSceneForest());

	this->currentSceneIndex = 0;
}

Application::~Application()
{
	for (Scene* scene : this->scenes) {
		delete scene;
	}
}

void Application::cycleScenes() {
	if (this->scenes.empty() == false) {
		this->currentSceneIndex = (this->currentSceneIndex + 1) % this->scenes.size();
		cout << "Switched to scene " << this->currentSceneIndex << endl;
	}
	return;
}

void Application::run()
{
	glEnable(GL_DEPTH_TEST); // Z-buffer
	while (!glfwWindowShouldClose(this->window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (this->scenes.empty() == false) {
			this->scenes[this->currentSceneIndex]->draw();
		}

		Camera& camera = scenes[currentSceneIndex]->camera;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			camera.move(glm::vec3(0.0f, 0.0f, 0.1f));
		}
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			camera.move(glm::vec3(0.0f, 0.0f, -0.1f));
		}
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
			camera.move(glm::vec3(-0.1f, 0.0f, 0.0f));
		}
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
			camera.move(glm::vec3(0.1f, 0.0f, 0.0f));
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
