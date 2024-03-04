#pragma once
#include "Sprite.h"
#include <vector>

class TileSpriteRenderer : public Sprite {
public:

	TileSpriteRenderer(int width, int height, float tileSize);
	~TileSpriteRenderer();

	// Function to initialize each tile.
	void initializeTiles();

	void setTileTexture(int x, int y, GLuint textureID);

	void render(unsigned int shaderProgram);

	const char* spritePath = "GameEngine/Include/Pictures/Sprites/Tilesets/plains.png";

	float x = 0.0f;
	float y = 0.0f;
	float spriteWidth = 1.0f;
	float spriteHeight = 1.0f;


private:
	int _width, _height;
	float _tileSize;
	std::vector<GLuint> _tiles; // Texture IDs for each tile.
};

