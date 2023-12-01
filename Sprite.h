#pragma once
#include <glm/ext/matrix_float4x4.hpp>

class Sprite
{
public:

	Sprite(const char* texturePath, float x, float y, float width, float height);
	~Sprite();

	void Draw(unsigned int shaderProgram);

private:
	unsigned int _VAO, _VBO, _EBO, _texture;
	glm::mat4 _modelMatrix;

	//Vertex Data
	static const float _vertices[];

	//Indices (or elements) for a simple quad.
	static const unsigned int _indices[];

	void _setupSprite();
};

