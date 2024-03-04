#include "Sprite.h"
#include <glm/ext/matrix_transform.hpp>
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

void EC2() {
	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		std::cerr << "OpenGL error: " << error << std::endl;
	}
}

const float Sprite::_vertices[] = {
	// positions          // color coords     // texture coords
	0.2f,  0.2f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
	0.2f, -0.2f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
   -0.2f, -0.2f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
   -0.2f,  0.2f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 1.0f  // top left 
};

const unsigned int Sprite::_indices[]{
	0, 1, 3, // first triangle
	1, 2, 3  // second triangle
};

Sprite::Sprite(const char* texturePath) {

	// Initialize variables
	_texturePath = texturePath;

	// Start texturing process
	//
	// Bind VAO, VBO, and EBO
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	// Set position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Set color coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Set texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Load and create the texture
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Set the texture filtering parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load the image, create texture, generate mipmaps.
	int stbi_width, stbi_height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(texturePath, &stbi_width, &stbi_height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, stbi_width, stbi_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		//std::cout << "Texture Width: " << stbi_width << ", Height: " << stbi_height << std::endl;
	}
	else {
		std::cout << "Failed to load texture: " << texturePath << std::endl;
	}
	stbi_image_free(data);

	glBindVertexArray(0); //Unbind the VAO.

}

Sprite::~Sprite()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteTextures(1, &_texture);
}


void Sprite::reloadData()
{
	// Start texturing process
	//
	// Bind VAO, VBO, and EBO
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	// Set position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Set color coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// Set texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Load and create the texture
	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture);

	// Set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	// Set the texture filtering parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load the image, create texture, generate mipmaps.
	int stbi_width, stbi_height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(_texturePath, &stbi_width, &stbi_height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, stbi_width, stbi_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		//std::cout << "Texture Width: " << stbi_width << ", Height: " << stbi_height << std::endl;
	}
	else {
		std::cout << "Failed to load texture: " << _texturePath << std::endl;
	}
	stbi_image_free(data);

	glBindVertexArray(0); //Unbind the VAO.
}

// ---- Utility Functions ---- //
// 
//	| Getters |
// 
// Returns the VAO of the sprite
GLuint Sprite::getVAO() const {
	return _VAO;
}

// Returns the texture of the sprite
GLuint Sprite::getTexture() const
{
	return _texture;
}

// Returns the sprite's associated texture path
const char* Sprite::getTexturePath()
{
	return _texturePath;
}

//
// | Setters | 
//
// Sets the sprite's associated texture path
void Sprite::setTextureFilePath(const char* texturePath)
{
	_texturePath = texturePath;
}


