#pragma once
#include "Player.h"

class World
{

private:

	// A storage container for all of the gameObjects in the world
	std::vector<GameObject> gameObjects;

	// Create the playerSprite object
	Sprite playerSprite;

	// Create the player object
	Player player;

	// Grass sprite for debugging
	Sprite grassSprite;

	// Grass object for debugging
	GameObject grassObject;


public:

	World();
	~World();

	void addGameObject(const GameObject& gameObject);

	void checkCollisions();

	void update(GLFWwindow* window, float deltaTime, float playerMoveSpeed);
	void render(GLFWwindow* window, unsigned int shaderProgram);

	// wip
	void printGameObjects();

};