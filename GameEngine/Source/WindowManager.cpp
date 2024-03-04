#include "WindowManager.h"
#include <iostream>

// Window Manager for the game
WindowManager::WindowManager()
	: SCR_HEIGHT(1080), SCR_WIDTH(800)
{
	
}

// Terminate the glfw window
WindowManager::~WindowManager()
{
	glfwTerminate();
}

// Runs the game window
int WindowManager::runWindow()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_HEIGHT, SCR_WIDTH, "2D RPG Testing", NULL, NULL);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD." << gladLoadGLLoader << std::endl;
		return -1;
	}
	
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create the Shader class object.
	Shader shader("GameEngine/Include/Shaders/vertexShader.glsl", "GameEngine/Include/Shaders/fragmentShader.glsl");

	// Create the GameEngine object to call rendering and logic functions.
	GameEngine gameEngine;

	// Create the gui manager object.
	guiManager gm(window);

	//Render loop. 
	while (!glfwWindowShouldClose(window)) {

		//input
		processInput(window);
		gameEngine.update(window);

		gameEngine.render(window, shader.use());

		gm.debugWindow();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteProgram(shader.use());

}

 void WindowManager::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void WindowManager::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}