#include "Bubble.h"

void Bubble::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht)
{
	Animated::init(tileMapPos, shaderProgram, sprtsht);
	setColisionFlags(0b1110);
	doGravity(false);
	size = glm::ivec2(16, 16);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5f, 0.5f), &spritesheet, &shaderProgram);
}

void Bubble::update(int deltaTime)
{
	if (!paused)
	{
		Animated::update(deltaTime);
		cumulatedTime += deltaTime;

		//Aixó garanteix un tickrate de 20hz per a les pilotes evitant que es moguin massa ràpid sent una alternativa al deltaTime tradicional
		//que funciona millor amb jocs basats en integers on no podem fer servir decimals.
		if (cumulatedTime > 50)
		{
			cumulatedTime -= 50;
			glm::ivec2 normal = map->collisionBubble(size.y, glm::vec2(pos.x + velocity.x + size.x / 2, pos.y + velocity.y + size.y / 2));
			if (velocity.x != 0 && normal.x != 0)
				velocity.x *= -1;
			if (velocity.y != 0 && normal.y != 0)
				velocity.y *= -1;
			velocity.y += (deltaTime / 200);
			pos += velocity;
			updatePosition();
		}
	}
}
