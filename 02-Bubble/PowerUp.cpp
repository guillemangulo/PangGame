#include "PowerUp.h"
#include "Joc.h"


void PowerUp::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int tip, const char* sprtsht)
{
	spritesheet.loadFromFile(sprtsht, TEXTURE_PIXEL_FORMAT_RGBA);
	tileMapDispl = tileMapPos;
	sprite = Sprite::createSprite(glm::ivec2(20, 20), glm::vec2(0.25f, 0.25f), &spritesheet, &shaderProgram);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	setColisionFlags(0b1001);
	setType(tip);
	size = glm::ivec2(10 * SCALING, 10 * SCALING);
}

void PowerUp::update(int deltaTime)
{
	if (!paused)
	{
		Animated::update(deltaTime);
		currTime += deltaTime;

		if (currTime >= timeOut *  0.85f)
		{
			sprite->setParpadeig(true);
		}
		if (currTime >= timeOut)
		{
			joc->removePowerUP(index);
		}
	}
}

void PowerUp::onCollision(short flags)
{
	if ((flags & 0b1000) == 0b1000)
	{
		collected = true;
		actPowerUp();
		joc->removePowerUP(index);
	}
	if ((flags & 0b0100) == 0b0100)
	{
	}
	if ((flags & 0b0001) == 0b0001)
	{
	}
	else if ((flags & 0b0010) == 0b0010)
	{
	}
}

void PowerUp::actPowerUp()
{
	switch (type)
	{
	case FREEZE_TIME:
	{
		joc->freezeTimePowerUp(3000);
		break;
	}
	case DYNAMITE:
	{
		//joc->dynamite();
		break;
	}
	case DOUBLE_WIRE:
	{
		
		joc->double_wire_powerup();
		break;
	}
	case POWER_WIRE:
	{
		//joc->powerWire();
		break;
	}
	case VULCAN_MISSILE:
	{
		//joc->vulcanMissile();
		break;
	}
	case INVINCIBILITY:
	{
		//joc->invincibility();
		break;
	}
	case SLOW_TIME:
	{
		joc->slowTimePowerUp(3000);
		break;
	}
	default:
		break;
	}
}

void PowerUp::setType(int tip)
{
	type = tip;
	switch (tip)
	{
	case FREEZE_TIME:
	{
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 1);
		sprite->addKeyframe(0, glm::vec2(3.f/ 4.f, 0));
		sprite->changeAnimation(0);
		updatePosition();
		break;
	}
	case DYNAMITE:
		break;
	case DOUBLE_WIRE:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(2.f / 4.f, 3.f / 4.f));
		sprite->changeAnimation(0);
		updatePosition();
		break;
	case POWER_WIRE:
		break;
	case VULCAN_MISSILE:
		break;
	case INVINCIBILITY:
		break;
	case SLOW_TIME:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 1);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 4.f));
		sprite->changeAnimation(0);
		updatePosition();
		break;
	default:
		break;
	}
}

