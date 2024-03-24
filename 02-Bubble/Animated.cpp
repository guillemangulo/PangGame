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
	if (doGrav)
	{
		short col = map->collisionMove(&pos, size, sizeoff, glm::ivec2(0, fallTable[fallFrame]));
		fallStateUpdate(col, deltaTime);
	}
	sprite->update(deltaTime);
}

void Animated::render()
{
	sprite->render();
	if (debugColision)
		drawColisionBox(&pos, size, sizeoff);
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

void Animated::updatePosition()
{
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

void Animated::drawColisionBox(glm::ivec2* pos, const glm::ivec2& size, const glm::ivec2& sizeoff, const glm::ivec2 dir) const
{
	if (debugColision)
	{
		// guardem la matriu actual
		glPushMatrix();

		// dibuixem la capsa de direccio si cal
		if (dir.x != 0 || dir.y != 0)
		{
			glBegin(GL_LINES);
			glColor3f(1.0f, 1.0f, 0.0f);
			glVertex2i(pos->x, pos->y);
			glVertex2i(pos->x + dir.x*4, pos->y + dir.y*4);
			glEnd();
		}

		// dibuixem la capsa de colisio
		glBegin(GL_LINE_LOOP);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2i(pos->x+sizeoff.x , pos->y+sizeoff.y );
		glVertex2i(pos->x + size.x + sizeoff.x, pos->y + sizeoff.y);
		glVertex2i(pos->x + size.x + sizeoff.x, pos->y + size.y + sizeoff.y);
		glVertex2i(pos->x + sizeoff.x, pos->y + size.y + sizeoff.y);
		glEnd();

		// restaurem la matriu
		glPopMatrix();
	}
}


void Animated::debugColisionBoxToggle()
{
	debugColision = !debugColision;
}


/// <summary>
/// Animació sencilla de com ha de caure un objecte basada en una lookup table
/// </summary>
/// <param name="deltaTime">En desus actualment, el mantinc per posibles optimitzacions.</param>
void Animated::fallStateUpdate(short col, int deltaTime)
{
	if (doGrav)
	{
		//TODO: Implementar size offset
		if (col & 0b0001)
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
		}
	}
}
