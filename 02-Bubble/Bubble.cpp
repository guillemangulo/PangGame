#include "Bubble.h"
#include <iostream>

void Bubble::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht)
{
	Animated::init(tileMapPos, shaderProgram, sprtsht);
	setColisionFlags(0b1110);
	doGravity(false);
	size = glm::ivec2(16, 16);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
}

void Bubble::update(int deltaTime)
{
	if (!paused)
	{
		Animated::update(deltaTime);
		glm::ivec2 normal = map->collisionBubble(size.y, glm::vec2(pos.x + velocity.x + size.x / 2, pos.y + velocity.y + size.y / 2));
		
		if (velocity.y != 0 && normal.y != 0)
			velocity.y *= -1;
		else if (velocity.x != 0 && normal.x != 0)
			velocity.x *= -1;

		#define vel 3
		gravStep++;
		if (gravStep % 4 == 0)
		{
			//Així no perdem moment en la gravetat
			velocity.y += 1;
			actVelocity = velocity.y;
			if(velocity.y > vel)
				actVelocity = vel;
			if(velocity.y < -vel)
				actVelocity = -vel;
		}

		pos += glm::ivec2(velocity.x, actVelocity);

		if (normal.y == 0 && pos.y + size.y > map->getTileSize() * (map->getMapSize().y -1))
		{
			pos.y = map->getTileSize() * (map->getMapSize().y -1) - size.y;
			velocity.y = -velocity.y;
		}
		updatePosition();
	}
}


void Bubble::onCollision(short flags) {
	std::cout << flags << endl;
}