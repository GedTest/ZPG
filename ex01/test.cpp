//Include GLEW
// important
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>  

//Include GLM  
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>


// TASKS
// glew dll zkopirovat do adresare kde je vysledna aplikace.exe tam nahrat knihofnu glwe32.dll
// upravit zdrojovz kod, vyhazet fixni pipline a nahradit programovatelna pipeline
// c > general > Additional Include Directories > ..\..\Libraries\glew-2.1.0\include
// pridat
// - Linker > input > glew32.lib
// - Linker > General > ..\..\Libraries\glew-2.1.0\lib\Release\Win32
// - v > general > ..\..\Libraries\glew - 2.1.0\include
// a v nazevprojektu\Debug nebo release zalezi co pouzivam tady nakopirovat glew32.dll z ..\..\Libraries\glew-2.1.0\lib\Release\Win32




// projekt
// shader program, abstract shader ze ktereho dedi vertex a fragment shader, shader manager, kreslitelnyObjekt nebo Model
// id shader programu bude private, zadny get/set, presuneme do tridy vse co potrebuje pracovat s danou private promennou,
// uvnitr tridy bude metoda, ktera s ni pracuje




static void error_callback(int error, const char* description) { fputs(description, stderr); }

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

float direction = 1;

void change_rotation_direction(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) { direction *= -1; }
}

//GLM test
/*
// Projection matrix : 45 Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);

// Camera matrix
glm::mat4 View = glm::lookAt(
	glm::vec3(10, 10, 10), // Camera is at (4,3,-3), in World Space
	glm::vec3(0, 0, 0), // and looks at the origin
	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
);
// Model matrix : an identity matrix (model will be at the origin)
glm::mat4 Model = glm::mat4(1.0f);
*/



int main(void)
{
	GLFWwindow* window;
	glfwSetErrorCallback(error_callback);
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	/* //inicializace konkretni verze
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE,
	GLFW_OPENGL_CORE_PROFILE);  //*/

	window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();


	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);


	
	float points[] = {
		 0.5f,  0.5f, 0.0f, 0, 0, 1,
		 -0.5f, -0.5f, 0.0f, 0, 0, 1,
		 0.5f, -0.5f, 0.0f, 0, 0, 1,
		
		//// additional vertices for square out of 2 triangles
		// 0.5f,  0.5f, 0.0f,
		// -0.5f, -0.5f, 0.0f,
		// -0.5f, 0.5f, 0.0f,
	};

	// uniform promenne muzu nastavovat
	const char* vertex_shader =
		"#version 330\n"
		"layout(location=0) in vec3 vp;"
		"layout(location=1) in vec3 vn;"
		"uniform mat4 modelMatrix;"			
		"out vec3 color;"
		"void main () {"
		"color = vn;"
		"     gl_Position = modelMatrix * vec4(vp, 1.0);"
		"}";



	const char* fragment_shader =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (0.5, 0.5, 0.5, 1.0);"
		"}";



	const char* second_fragment =
		"#version 330\n"
		"out vec4 frag_colour;"
		"void main () {"
		"     frag_colour = vec4 (0.0, 0.7, 1.0, 1.0);"
		"}";



	GLuint VBO = 0;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);


	GLuint VAO = 0;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// what does bind the VAO mean

	glEnableVertexAttribArray(0);	// position
	glEnableVertexAttribArray(1);	// normal

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

													// jeden vrchol ma velikost 6 floatu, zacina na zacatku
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
																		// preskoc prvni tri floaty
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));


	//create and compile shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);


	GLuint secondFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(secondFragment, 1, &second_fragment, NULL);
	glCompileShader(secondFragment);

	GLuint shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, fragmentShader);
	glAttachShader(shaderProgram, secondFragment);
	glAttachShader(shaderProgram, vertexShader);
	glLinkProgram(shaderProgram);



	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}


	glm::mat4 M = glm::mat4(1.0f); // construct identity matrix
	float angle = 0;
	float axisX = 1.0f;
	float axisY = 0.0f;
	float axisZ = 1.0f;
	//M = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, axisY, 0.0f));
	//M = glm::rotate(M, angle, glm::vec3(1.0f, 0.0f, 0.0f));
	//M = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, myView));

	while (!glfwWindowShouldClose(window)) {
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// glUseProgram(0) // tedy nenastavi se zadny shader na vykresleni
		glUseProgram(shaderProgram);

		// new
		M = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(axisX, axisY, axisZ));
		//M = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		GLint idModelTransform = glGetUniformLocation(shaderProgram, "modelMatrix");
		glUniformMatrix4fv(idModelTransform, 1, GL_FALSE, &M[0][0]);
		angle += 1.f * 0.016f;
		// new
		
		glBindVertexArray(VAO);
		// draw triangles
		// pro ctverec
		// 2880 pro kouli
		glDrawArrays(GL_TRIANGLES, 0, 6);
		//glDrawArrays(GL_TRIANGLES, 0, 3); //mode,first,count
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);

	glfwTerminate();
	exit(EXIT_SUCCESS);
}



// programovatelna pipeline obsahuje shadery, ktere budeme programovat
// fixni pipeline, chova se jako stavovy automat