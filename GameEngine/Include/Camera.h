#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{

private:

	float _screenWidth;
	float _screenHeight;
	glm::mat4 _orthoProjectionMatrix;
	glm::mat4 _viewMatrix;
	glm::vec3 _position;


public:


	Camera(float screenWidth, float screenHeight);

	void setView(glm::mat4 playerModelMatrix, glm::vec3 playerPosition, unsigned int shaderProgram);

};

