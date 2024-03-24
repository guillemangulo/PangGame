#include <cmath>
#include <iostream>
#include <GL/glew.h>

#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4



void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, const char* sprtsht)
{
	size = glm::ivec2(16, 32);
	sizeoff = glm::ivec2(8, 0);
	spritesheet.loadFromFile(sprtsht, TEXTURE_PIXEL_FORMAT_RGBA);
	#define SPRITE_BLOCK 0.125f
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(SPRITE_BLOCK, SPRITE_BLOCK), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(9);
	
		sprite->setAnimationSpeed(STAND_LEFT, 8);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(SPRITE_BLOCK * 7, SPRITE_BLOCK * 0));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(SPRITE_BLOCK * 0, SPRITE_BLOCK * 0));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 8);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(SPRITE_BLOCK * 7, SPRITE_BLOCK * 0));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(SPRITE_BLOCK * 6, SPRITE_BLOCK * 0));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(SPRITE_BLOCK * 5, SPRITE_BLOCK * 0));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(SPRITE_BLOCK * 6, SPRITE_BLOCK * 1));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(SPRITE_BLOCK * 5, SPRITE_BLOCK * 1));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 8);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(SPRITE_BLOCK * 0, SPRITE_BLOCK * 0));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(SPRITE_BLOCK * 1, SPRITE_BLOCK * 0));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(SPRITE_BLOCK * 2, SPRITE_BLOCK * 0));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(SPRITE_BLOCK * 3, SPRITE_BLOCK * 0));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(SPRITE_BLOCK * 4, SPRITE_BLOCK * 0));

		sprite->setAnimationSpeed(SHOOT, 8);
		sprite->addKeyframe(SHOOT, glm::vec2(SPRITE_BLOCK * 0, SPRITE_BLOCK * 3));
		sprite->addKeyframe(SHOOT, glm::vec2(SPRITE_BLOCK * 1, SPRITE_BLOCK * 3));

		sprite->setAnimationSpeed(CLIMB_UP, 8);
		sprite->addKeyframe(CLIMB_UP, glm::vec2(SPRITE_BLOCK * 0, SPRITE_BLOCK * 1));
		sprite->addKeyframe(CLIMB_UP, glm::vec2(SPRITE_BLOCK * 1, SPRITE_BLOCK * 1));
		sprite->addKeyframe(CLIMB_UP, glm::vec2(SPRITE_BLOCK * 2, SPRITE_BLOCK * 1));
		sprite->addKeyframe(CLIMB_UP, glm::vec2(SPRITE_BLOCK * 3, SPRITE_BLOCK * 1));

		sprite->setAnimationSpeed(CLIMB_DOWN, 8);
		sprite->addKeyframe(CLIMB_DOWN, glm::vec2(SPRITE_BLOCK * 0, SPRITE_BLOCK * 2));
		sprite->addKeyframe(CLIMB_DOWN, glm::vec2(SPRITE_BLOCK * 0, SPRITE_BLOCK * 2));
		sprite->addKeyframe(CLIMB_DOWN, glm::vec2(SPRITE_BLOCK * 0, SPRITE_BLOCK * 2));

		sprite->setAnimationSpeed(TAKE_DAMAGE, 8);
		sprite->addKeyframe(TAKE_DAMAGE, glm::vec2(SPRITE_BLOCK * 4, SPRITE_BLOCK * 2));

		sprite->setAnimationSpeed(END_CLIMB, 8);
		sprite->addKeyframe(END_CLIMB, glm::vec2(SPRITE_BLOCK * 3, SPRITE_BLOCK * 2));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);

	//Direcció que indica el jugador
	glm::ivec2 joy = Game::instance().getDirection();

	if (joy.y != 0)
	{
		//TODO:: Implementar escales
		cout << "do stairs" << endl;
	}
	glm::ivec2 dir;

	if (doGrav)
		dir = glm::ivec2(joy.x * speed, fallTable[fallFrame]);
	else
		dir = glm::ivec2(joy.x * speed, 0);

	short col = map->collisionMove(&pos, size,sizeoff, dir);
	if(doGrav)
		fallStateUpdate(col,deltaTime);

	//Actualitzem les animacions en funció de la direcció i les colisions
	if (dir.x < 0)
	{
		if (sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		if (col & 0b1000)
		{
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if (dir.x > 0)
	{
		if (sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		if (col & 0b0100 )
		{
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else
	{
		if (sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}


	//Renderitzem el que cal
	updatePosition();	
}





