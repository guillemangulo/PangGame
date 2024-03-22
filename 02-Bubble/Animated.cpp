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
	fall(deltaTime);
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


/// <summary>
/// Defineix si l'objecte ha d'estar afectat per la gravetat o no
/// </summary>
/// <param name="gravity">Boolea de si está afectat</param>
/// <returns>Retorna si l'objecte te gravetat</returns>
bool Animated::doGravity(bool gravity)
{
	doGrav = gravity;
	return doGrav;
}


/// <summary>
/// Animació sencilla de com ha de caure un objecte basada en una lookup table
/// </summary>
/// <param name="deltaTime">En desus actualment, el mantinc per posibles optimitzacions.</param>
void Animated::fall(int deltaTime)
{
	if (doGrav)
	{
		if (map->collisionMove(&pos, glm::ivec2(1, 1), glm::ivec2(0,-1)) & 0b0001)
		{
			if (falling)
			{
				falling = false;
				fallFrame = 0;
			}
		}
		else
		{
			if (!falling)
			{
				falling = true;
			}
			fallFrame += 1;
			if (fallFrame >= fallTableSize)
			{
				fallFrame = fallTableSize-1;
			}
			pos.y -= fallTable[fallFrame];
			sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
		}
	}
}
