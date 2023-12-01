#include "Sprite.h"
#include <glm/ext/matrix_transform.hpp>
#include <glad/glad.h>
#include <stb_image.h>
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

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

Sprite::Sprite(const char* texturePath, float x, float y, float width, float height) {

	_modelMatrix = glm::mat4(1.0f);
	_modelMatrix = glm::translate(_modelMatrix, glm::vec3(x, y, 0.0f));
	_modelMatrix = glm::scale(_modelMatrix, glm::vec3(width, height, 1.0f));

	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);

	_setupSprite();

	glBindBuffer(GL_ARRAY_BUFFER, _VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_vertices), _vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(_indices), _indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color coord attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	// texture coord attribute
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
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture: " << texturePath << std::endl;
	}
	stbi_image_free(data);

	glBindVertexArray(0); //Unbind the VAO.
}

void Sprite::_setupSprite() {

}

void Sprite::Draw(unsigned int shaderProgram) {
	glUseProgram(shaderProgram);

	// Set shader uniforms
	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

	// Set model matrix uniform 
	glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(_modelMatrix));

	// Bind texture on corresponding texture units
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _texture);

    // Draw the sprite
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

Sprite::~Sprite() {
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(1, &_VBO);
	glDeleteTextures(1, &_texture);
}