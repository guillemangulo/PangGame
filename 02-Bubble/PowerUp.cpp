#include "PowerUp.h"


void PowerUp::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Type tip, const char* sprtsht)
{
	spritesheet.loadFromFile(sprtsht, TEXTURE_PIXEL_FORMAT_RGBA);
	tileMapDispl = tileMapPos;
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(0.5f, 0.5f), &spritesheet, &shaderProgram);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	setColisionFlags(0b1001);
	setType(tip);
}

void PowerUp::update(int deltaTime)
{
	Animated::update(deltaTime);
	if (!cleanable)
	{
		currTime += deltaTime;
		if (currTime >= timeOut)
		{
			cleanable = true;
		}
	}
}

void PowerUp::onCollision(short flags)
{
	if ((flags & 0b1000) == 0b1000)
	{
		collected = true;
		cleanable = true;
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

void PowerUp::setType(Type tip)
{
	type = tip;
	switch (tip)
	{
	case PowerUp::Type::FREEZE_TIME:
	{
		sprite->setNumberAnimations(1);
			sprite->setAnimationSpeed(0, 1);
			sprite->addKeyframe(0, glm::vec2(2, 1));
		sprite->changeAnimation(0);
		updatePosition();
		break;
	}
	case PowerUp::Type::DYNAMITE:
		break;
	case PowerUp::Type::DOUBLE_WIRE:
		break;
	case PowerUp::Type::POWER_WIRE:
		break;
	case PowerUp::Type::VULCAN_MISSILE:
		break;
	case PowerUp::Type::INVINCIBILITY:
		break;
	case PowerUp::Type::SLOW_TIME:
		break;
	default:
		break;
	}
}

