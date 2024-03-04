#include "GameEngine.h"
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtc/type_ptr.hpp>

void GameEngine::EC()
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << error << std::endl;
	}
}

GameEngine::GameEngine()
{
}

GameEngine::~GameEngine()
{

}

void GameEngine::init()
{
}

void GameEngine::update(GLFWwindow* window)
{
	// Set up the lastFrameTime for calculating deltaTime.
	static double lastFrameTime = glfwGetTime();

	// Calculate deltaTime
	double currentFrameTime = glfwGetTime();
	float deltaTime = static_cast<float>(currentFrameTime - lastFrameTime);
	lastFrameTime = currentFrameTime;

	// Update the world
	world.update(window, deltaTime, playerMoveSpeed);
	
}

void GameEngine::render(GLFWwindow* window, unsigned int shaderProgram)
{

	//render
	glClearColor(0.3f, 0.3f, 0.4f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Render the world
	world.render(window, shaderProgram);

	EC();
}