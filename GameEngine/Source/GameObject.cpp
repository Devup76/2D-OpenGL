#include "GameObject.h"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



GameObject::GameObject(Sprite& sprite, glm::vec3 position, float width, float height, const std::string name)
	: sprite(sprite), _texture(sprite.getTexture()), _VAO(sprite.getVAO()), _position(position), _width(width), _height(height), _name(name)
{
	_modelMatrix = glm::mat4(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, glm::vec3(_position.x, _position.y, 0.0f));
	_modelMatrix = glm::scale(_modelMatrix, glm::vec3(width, height, 1.0f));

	float halfWidth = width * 0.5f;
	float halfHeight = height * 0.5f;

	const float boundingBoxVertices[] = {
		-halfWidth, -halfHeight, 0.0f,
		 halfWidth, -halfHeight, 0.0f,
		 halfWidth,  halfHeight, 0.0f,
		-halfWidth,  halfHeight, 0.0f
	};

	// Create VAO and VBO
	glGenVertexArrays(1, &boundingBoxVAO);
	glGenBuffers(1, &boundingBoxVBO);

	// Bind VAO
	glBindVertexArray(boundingBoxVAO);

	// Bind VBO and set data
	glBindBuffer(GL_ARRAY_BUFFER, boundingBoxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(boundingBoxVertices), boundingBoxVertices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Unbind VAO
	glBindVertexArray(0);

}

GameObject::~GameObject()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteTextures(1, &_texture);
}

void GameObject::render(unsigned int shaderProgram, glm::mat4 modelMatrix)
{
	glUseProgram(shaderProgram);

	// Set shader uniforms
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

	// Set model matrix uniform 
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind texture on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);

	// Print X, Y loc of the object.
	// std::cout << "x: " << objectPosition.x << " " << "y: " << objectPosition.y << std::endl;

	// Draw the sprite
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Draw bounding box
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glBindVertexArray(boundingBoxVAO);
	glDrawArrays(GL_LINE_LOOP, 0, 4);
	glBindVertexArray(0);
}

glm::mat4 GameObject::getModelMatrix()
{
	return _modelMatrix;
}

glm::vec3 GameObject::getPos()
{
	return _position;
}

float GameObject::getWidth()
{
	return _width;
}

float GameObject::getHeight()
{
	return _height;
}

std::string GameObject::getName()
{
	return _name;
}


void GameObject::setModelMatrix(glm::mat4 modelMatrix)
{
	_modelMatrix = modelMatrix;
}

void GameObject::setPos(glm::vec3 position)
{
	_position = position;
}

void GameObject::setWidth(float width)
{
	_width = width;
}

void GameObject::setHeight(float height)
{
	_height = height;
}