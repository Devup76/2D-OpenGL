#include "Player.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Player::Player(Sprite& sprite, glm::vec3 position, float width, float height)
	: _gameObject(sprite, position, width, height, "player"), _camera(1080.0f, 800.0f), _modelMatrix(_gameObject.getModelMatrix()), _position(_gameObject.getPos())
{

}

Player::~Player()
{

}

void Player::render(unsigned int shaderProgram)
{	
	_camera.setView(_modelMatrix, _position, shaderProgram);
	_gameObject.render(shaderProgram, _modelMatrix);
}

void Player::handleInput(GLFWwindow* window, float deltaTime, float moveSpeed) {
	// Current position
	glm::vec3 movementOffset(0.0f);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		movementOffset.y += moveSpeed * deltaTime;
	}
		
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		movementOffset.y -= moveSpeed * deltaTime;
	}
		
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		movementOffset.x -= moveSpeed * deltaTime;
	}
		
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		movementOffset.x += moveSpeed * deltaTime;
	}

	_position += movementOffset;
	_modelMatrix = glm::translate(_modelMatrix, movementOffset);
}

void Player::checkCollisions(GameObject& gameObject)
{
	const float epsilon = 0.001f;
	if (_position.x < gameObject.getPos().x + gameObject.getWidth() + epsilon &&    // East
		_position.x + getWidth() > gameObject.getPos().x - epsilon &&				// West
		_position.y < gameObject.getPos().y + gameObject.getHeight() + epsilon &&   // North
		_position.y + getHeight() > gameObject.getPos().y - epsilon)				// South
	{
		std::cout << "Collision" << std::endl;
	}
	else {
		//std::cout << "No collision" << std::endl;
	}
}

glm::mat4 Player::getPlayerModelMatrix()
{
	return _modelMatrix;
}

GameObject Player::getGameObject()
{
	return _gameObject;
}

glm::vec3 Player::getPos()
{
	return _position;
}

glm::vec3 Player::getMovementOffset()
{
	return _offset;
}

glm::vec2 Player::getDimensions()
{
	return glm::vec2(_gameObject.getWidth(), _gameObject.getHeight());
}

float Player::getHeight()
{
	return _gameObject.getHeight();
}

float Player::getWidth()
{
	return _gameObject.getWidth();
}


// ------ SETTERS -------
//
// Set the movement offset
void Player::setMovementOffset(glm::vec3 offset)
{
	_offset = offset;
}
