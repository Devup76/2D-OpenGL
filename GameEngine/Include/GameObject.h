#pragma once
#include "Sprite.h"
#include <iostream>

#include <box2d/box2d.h>
#include <box2d/b2_api.h>
#include <box2d/b2_math.h>
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <string>

class GameObject
{
public:

	// Defines a game object to be used inside of the world
	GameObject(Sprite& sprite, glm::vec3 position, float width, float height, std::string name);

	// Destroys the game object
	~GameObject();

	// Render the game object
	void render(unsigned int shaderProgram, glm::mat4 _modelMatrix);

	// Get the game obejct's model matrix
	glm::mat4 getModelMatrix();

	// Get the game object's position
	glm::vec3 getPos();
	
	// Get the game object's width
	float getWidth();

	// Get the game object's height
	float getHeight();

	// Get the game object's name
	std::string getName();


	// Sets the game object's model matrix
	void setModelMatrix(glm::mat4 modelMatrix);

	// Sets the game object's position
	void setPos(glm::vec3 position);

	// Sets the game object's width
	void setWidth(float width);

	// Sets the game object's height
	void setHeight(float height);

private:

	// Sprite object of the game object
	Sprite sprite;

	// The game object's texture taken from the sprite object for rendering logic
	GLuint _texture;

	// The game object's VAO for rendering logic
	GLuint _VAO;

	// The game object's model matrix for transformation logic
	glm::mat4 _modelMatrix;

	// The game object's position in 2D space (by setting z to 0)
	glm::vec3 _position;

	// The game object's width and height
	float _width, _height;

	// The game object's name
	std::string _name;

	static const float boundingBoxVertices[];
	unsigned int boundingBoxVAO, boundingBoxVBO;

};

