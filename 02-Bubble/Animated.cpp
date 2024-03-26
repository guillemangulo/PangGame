#include "Animated.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>


void Animated::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht)
{
	spritesheet.loadFromFile(sprtsht, TEXTURE_PIXEL_FORMAT_RGBA);
    #define SPRITE_BLOCK 0.125f
	tileMapDispl = tileMapPos;
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(SPRITE_BLOCK, SPRITE_BLOCK), &spritesheet, &shaderProgram);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
}

void Animated::update(int deltaTime)
{
	if (!paused)
	{
		if (doGrav)
		{
			if((colisionFlags & 0b0001) == 0b0001)
			{
				int posy = pos.y+size.y;
				int posfloor = map->getTileSize() * (map->getMapSize().y-5);
				if (posy < posfloor)
				{
					pos.y += fallTable[fallFrame];
					updatePosition();
					fallStateUpdate(0b0000, deltaTime);
				}
				else
				{
					pos.y = posfloor;
					updatePosition();
					fallStateUpdate(0b0001, deltaTime);
				}
			}
			if ((colisionFlags & 0b0010) == 0b0010)
			{
				short col = map->collisionMove(&pos, size, sizeoff, glm::ivec2(0, fallTable[fallFrame]));
				fallStateUpdate(col, deltaTime);
			}
		}
		sprite->update(deltaTime);
	}
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

bool Animated::pausa(bool pausa)
{
	if(pausa == NULL)
		paused = !paused;
	else
		paused = pausa;
	return paused;
}

void Animated::setColisionFlags(short flags)
{
	if((flags & 0b0011) == 0b0011)
	{
		colisionFlags = flags & 0b1110;
	}
	else
	{
		colisionFlags = flags;
	}
	
}

bool Animated::doGravity(bool gravity)
{
	if(gravity == NULL)
	{
		doGrav = !doGrav;
	}
	else
	{
		doGrav = gravity;
	}
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
