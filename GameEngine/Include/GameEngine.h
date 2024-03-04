#pragma once
#include "World.h"
#include "GameObject.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GameEngine
{

private:

	// Create the world object
	World world;

	// Player Move Speed
	float playerMoveSpeed = 1.5f;

	// Utility
	void EC();

public:

	// Game Engine for the game. Runs the bulk of the programs. A sort of central hub?
	GameEngine();

	// Terminate the game engine.
	~GameEngine();

	// Initialize the Game Engine -- WIP --
	void init();

	// Update the game with inputs
	void update(GLFWwindow* window);

	// Runs all of the game's logic 
	void render(GLFWwindow* window, unsigned int shaderProgram);

};