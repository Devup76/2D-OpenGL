#pragma once
#include "guiManager.h"
#include "Shader.h"

class WindowManager
{

private:

	const unsigned int SCR_WIDTH;
	const unsigned int SCR_HEIGHT;
	//GLFWwindow* window = createWindow();

public:
	// Window Manager for the game
	WindowManager();

	// Terminate the glfw window.
	~WindowManager();

	// Run the game window
	int runWindow();

	// Framebuffer for glfw
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	// Process game input
	void processInput(GLFWwindow* window);

};

