#pragma once
#include "GameObject.h"
#include "Camera.h"
#include <vector>

class Player
{
public:

	// Define's the player object to be used inside of the world.
	Player(Sprite& sprite, glm::vec3 position, float width, float height);

	// Destroy the player object and remove it from the world.
	~Player();

	// Render the player sprite
	void render(unsigned int shaderProgram);

	// Handle the player's keyboard input
	void handleInput(GLFWwindow* window, float deltaTime, float moveSpeed);

	void checkCollisions(GameObject& gameObject);

	// Get the player's model matrix
	glm::mat4 getPlayerModelMatrix();

	// Get the player's GameObject
	GameObject getGameObject();

	// Get the player's position
	glm::vec3 getPos();

	// Get the player's movement offset
	glm::vec3 getMovementOffset();

	// Get the player's width and height
	glm::vec2 getDimensions();

	float getHeight();
	float getWidth();

	// ------ SETTERS ------
	//
	// Set the player's movement offset
	void setMovementOffset(glm::vec3 offset);

private:

	// The player's game object
	GameObject _gameObject;

	// The camera for the game
	Camera _camera;

	// The player's model matrix used for transformation logic
	glm::mat4 _modelMatrix;

	// The player's position
	glm::vec3 _position;

	// The player's movement offset
	glm::vec3 _offset;

	// Flags to verify movement
	// TODO: make flags
	bool northCollision;
	bool eastCollision;
	bool southCollision;
	bool westCollision;
};

