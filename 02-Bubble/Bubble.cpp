#include "Bubble.h"
#include <iostream>

void Bubble::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht, int diam)
{
	Animated::init(tileMapPos, shaderProgram, sprtsht);
	setColisionFlags(0b1110);
	doGravity(false);
	int randx = std::rand() % 4 - 2;
	int randy = std::rand() % 4 - 2;
	velocity = glm::ivec2(randx != 0 ? randx:1 , randy!= 0? randy:1);
	size = glm::ivec2(diam, diam);
	sprite = Sprite::createSprite(glm::ivec2(64, 64), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);
	sprite->setAnimationSpeed(0, 1);
	int scale = 0;
	if (diam == 32)
		scale = 1;
	else if (diam == 16)
		scale = 2;
	else if (diam == 8)
		scale = 3;
	sprite->addKeyframe(0, glm::vec2(0.25f*scale, 0.25f*(std::rand()%4)));

	sprite->changeAnimation(0);
}

bool Bubble::circleRect(float rx, float ry, float rw, float rh) {

	// temporary variables to set edges for testing
	float testX = pos.x;
	float testY = pos.y;

	// which edge is closest?
	if (pos.x < rx)         testX = rx;      // test left edge
	else if (pos.x > rx + rw) testX = rx + rw;   // right edge
	if (pos.y < ry)         testY = ry;      // top edge
	else if (pos.y > ry + rh) testY = ry + rh;   // bottom edge

	// get distance from closest edges
	float distX = pos.x - testX;
	float distY = pos.y - testY;
	float distance = sqrt((distX * distX) + (distY * distY));

	// if the distance is less than the radius, collision!
	if (distance <= size.x) {
		return true;
	}
	return false;
}


void Bubble::update(int deltaTime)
{
	if (!paused)
	{
		sprite->update(deltaTime);

/*#define vel 5
		gravStep++;
		if (gravStep % 4 == 0)
		{
			//Així no perdem moment en la gravetat
			velocity.y += 1;
			actVelocity = velocity.y;
			if (velocity.y > vel)
				actVelocity = vel;
			if (velocity.y < -vel)
				actVelocity = -vel;
		}//*/

		//distancia al bloc més proper
		glm::ivec2 dist = map->collisionBubble(size.y/2, glm::ivec2(pos.x + 32, pos.y+ 32), glm::ivec2(velocity.x,velocity.y));

		
		if (abs(dist.x) < abs(dist.y))
		{
			if (dist.y > 0 && velocity.y > 0)
			{
				velocity.y = -velocity.y;
			}
			else if (dist.y < 0 && velocity.y < 0)
			{
				velocity.y = -velocity.y;
			}
		}
		else if (abs(dist.x) > abs(dist.y))
		{
			if (dist.x > 0 && velocity.x > 0)
			{
				velocity.x = -velocity.x;
			}
			else if (dist.x < 0 && velocity.x < 0)
			{
				velocity.x = -velocity.x;
			}
		}

		pos += glm::ivec2(velocity.x, velocity.y);
		updatePosition();
	}
}


void Bubble::onCollision(short flags) {
	std::cout << flags << endl;
}