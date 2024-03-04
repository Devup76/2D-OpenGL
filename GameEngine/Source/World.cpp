#include "World.h"
#include <glm/gtc/type_ptr.hpp>
#include <guiManager.h>

World::World()
	: playerSprite("GameEngine/Include/Pictures/Sprites/cute-ghost-transparent-7.png"),
	player(playerSprite, glm::vec3(0.0f, 0.0f, 0.0f), 0.5f, 0.5f),
	grassSprite("GameEngine/Include/Pictures/Sprites/grass.png"),
	grassObject(grassSprite, glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 1.0f, "grass")
{
	addGameObject(grassObject);
}

World::~World()
{
}

void World::addGameObject(const GameObject& gameObject)
{
	gameObjects.push_back(gameObject);
}

void World::checkCollisions()
{
	for (GameObject& gameObject : gameObjects) {
		//std::cout << "Checking collisions for: " << gameObject.getName() << std::endl;
		//std::cout << "Player Coord: " << player.getPos().x << ", " << player.getPos().y << std::endl;
		//std::cout << "Player Dimensions: " << player.getDimensions().x << ", " << player.getDimensions().y << std::endl;
		//std::cout << "Grass Coord: " << gameObject.getPos().x << ", " << gameObject.getPos().y << std::endl;
		//std::cout << "Grass Dimensions: " << gameObject.getWidth() << ", " << gameObject.getHeight() << std::endl;
		player.checkCollisions(gameObject);
	}
}

void World::update(GLFWwindow* window, float deltaTime, float playerMoveSpeed)
{
	// Update player transformation based on user input.
	player.handleInput(window, deltaTime, playerMoveSpeed);
}

void World::render(GLFWwindow* window, unsigned int shaderProgram)
{
	// Draw the player object's sprite
	player.render(shaderProgram);

	for (GameObject& gameObject : gameObjects) {
		gameObject.render(shaderProgram, gameObject.getModelMatrix());
	}

	//grassObject.render(shaderProgram, grassObject.getModelMatrix());
	checkCollisions();
}

void World::printGameObjects()
{
	for (GameObject& gameObject : gameObjects) {
		std::cout << "Work-in-progress." << std::endl;
	}
}