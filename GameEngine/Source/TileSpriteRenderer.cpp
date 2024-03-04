#include "TileSpriteRenderer.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

TileSpriteRenderer::TileSpriteRenderer(int width, int height, float tileSize)
    : Sprite(spritePath),
    _width(width), _height(height), _tileSize(tileSize) {
	initializeTiles();
}

void TileSpriteRenderer::initializeTiles() {
	_tiles.resize(_width * _height, 0);
}

void TileSpriteRenderer::setTileTexture(int y, int x, GLuint textureID) {
	int index = y * _width + x;
	if (index >= 0 && index < _tiles.size()) {
		_tiles[index] = textureID;
	}
}

void TileSpriteRenderer::render(unsigned int shaderProgram) {
	glUseProgram(shaderProgram);

	glUniform1i(glGetUniformLocation(shaderProgram, "texture1"), 0);

    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            int index = y * _width + x;
            if (_tiles[index] != 0) {
                glm::mat4 tileModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x * _tileSize, y * _tileSize, 0.0f));
                tileModelMatrix = glm::scale(tileModelMatrix, glm::vec3(_tileSize, _tileSize, 1.0f));

                glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "transform"), 1, GL_FALSE, glm::value_ptr(tileModelMatrix));

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, _tiles[index]);

                glBindVertexArray(Sprite::getVAO());
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);
            }
        }
    }
}

TileSpriteRenderer::~TileSpriteRenderer() {

}