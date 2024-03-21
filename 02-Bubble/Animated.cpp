#include "Animated.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>


void Animated::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht)
{
	spritesheet.loadFromFile(sprtsht, TEXTURE_PIXEL_FORMAT_RGBA);
    #define SPRITE_BLOCK 0.125f
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));

}

void Animated::update(int deltaTime)
{
	sprite->update(deltaTime);
}

void Animated::render()
{
	sprite->render();
}

void Animated::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Animated::setPosition(const glm::vec2& _pos)
{
	pos = _pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}
