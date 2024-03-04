#pragma once
#include <glm/ext/matrix_float4x4.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

class Sprite
{
public:

	// Defines a sprite to use inside of the game engine
	Sprite(const char* texturePath);
	~Sprite();

	void reloadData();

	// ---- Utility Functions ---- //
	
	// 
	//	| Getters |
	// 
	
	// Returns the VAO of the sprite
	GLuint getVAO() const;

	// Returns the texture of the sprite
	GLuint getTexture() const;

	// Returns the sprite's assoicated texture file path.
	const char* getTexturePath();
	
	//
	// | Setters |
	//

	// Sets the sprite's associated texture file path.
	void setTextureFilePath(const char* texturePath);

private:

	// The sprite texture's assocaiated file path
	const char* _texturePath;

	unsigned int _VAO, _VBO, _EBO, _texture;

	//Vertex Data
	static const float _vertices[];

	//Indices (or elements) for a simple quad.
	static const unsigned int _indices[];

};