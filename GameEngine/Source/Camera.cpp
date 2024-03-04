#include "Camera.h"
#include "glad/glad.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

Camera::Camera(float screenWidth, float screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
	_orthoProjectionMatrix = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight, -1.0f, 1.0f);
	_viewMatrix = glm::mat4(1.0f);
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Camera::setView(glm::mat4 playerModelMatrix, glm::vec3 playerPosition, unsigned int shaderProgram)
{
	std::cout << "Player Position: " << playerPosition.x << ", " << playerPosition.y << std::endl;
	//std::cout << "Camera Position: " << _position.x << ", " << _position.y << std::endl;

	_viewMatrix = glm::inverse(playerModelMatrix);

	glm::mat4 zoomMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
	_viewMatrix = zoomMatrix * _viewMatrix;

	unsigned int viewLocation = glGetUniformLocation(shaderProgram, "view");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(_viewMatrix));
}
