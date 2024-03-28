#include "Food.h"
#include "Joc.h"

void Food::update(int deltaTime)
{
	if (!paused)
	{
		Animated::update(deltaTime);
		currTime += deltaTime;
		if (currTime >= timeOut)
		{
			joc->removeFood(index);
		}
	}
}

void Food::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int tip, const char* sprtsht)
{
	spritesheet.loadFromFile(sprtsht, TEXTURE_PIXEL_FORMAT_RGBA);
	tileMapDispl = tileMapPos;
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(1.f/7.f, 1.f/7.f), &spritesheet, &shaderProgram);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
	setColisionFlags(0b1001);
	setTipus(tip);
}

void Food::onCollision(short flags)
{
	if ((flags & 0b1000) == 0b1000)
	{
		joc->addPointsJ1(calcularPunts());
		joc->removeFood(index);
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

int Food::calcularPunts()
{
	switch (type)
	{
	case Food::cherries:
		return 500;
		break;
	case Food::lemon:
		return 1000;
		break;
	case Food::banana:
		return 2000;
		break;
	case Food::orange:
		return 3000;
		break;
	case Food::watermelon:
		return 4000;
		break;
	case Food::pineapple:
		return 5000;
		break;
	case Food::grapes:
		return 6000;
		break;
	case Food::apple:
		return 7000;
		break;
	case Food::strawberry:
		return 8000;
		break;
	case Food::honeydew:
		return 9000;
		break;
	case Food::pickle:
		return 10000;
		break;
	case Food::eggplant:
		return 12000;
		break;
	case Food::tomato:
		return 14000;
		break;
	case Food::squash:
		return 16000;
		break;
	case Food::carrot:
		return 18000;
		break;
	case Food::corn:
		return 20000;
		break;
	case Food::green_pepper:
		return 22000;
		break;
	case Food::radish:
		return 24000;
		break;
	case Food::mushroom:
		return 26000;
		break;
	case Food::bean:
		return 28000;
		break;
	case Food::hamburger:
		return 30000;
		break;
	case Food::hotdog:
		return 33000;
		break;
	case Food::wiener:
		return 36000;
		break;
	case Food::doughnut:
		return 39000;
		break;
	case Food::chicken_drumstick:
		return 42000;
		break;
	case Food::french_fries:
		return 45000;
		break;
	case Food::shrimp_nigiri:
		return 48000;
		break;
	case Food::cake:
		return 50000;
		break;
	default:
		break;
	}
}

void Food::setTipus(int tipus)
{
	type = tipus;
	switch (type)
	{
	case Food::cherries:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 0.f));
		sprite->changeAnimation(0);
		break;
	case Food::lemon:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(1.f / 7.f, 0.f));
		sprite->changeAnimation(0);
		break;
	case Food::banana:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(2.f / 7.f, 0.f));
		sprite->changeAnimation(0);
		break;
	case Food::orange:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(3.f / 7.f, 0.f));
		sprite->changeAnimation(0);
		break;
	case Food::watermelon:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(4.f / 7.f, 0.f));
		sprite->changeAnimation(0);
		break;
	case Food::pineapple:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(5.f / 7.f, 0.f));
		sprite->changeAnimation(0);
		break;
	case Food::grapes:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(6.f / 7.f, 0.f));
		sprite->changeAnimation(0);
		break;
	case Food::apple:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 1.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::strawberry:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(1.f / 7.f, 1.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::honeydew:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(2.f / 7.f, 1.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::pickle:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(3.f / 7.f, 1.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::eggplant:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(4.f / 7.f, 1.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::tomato:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(5.f / 7.f, 1.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::squash:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(6.f / 7.f, 1.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::carrot:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 2.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::corn:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(1.f / 7.f, 2.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::green_pepper:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(2.f / 7.f, 2.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::radish:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(3.f / 7.f, 2.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::mushroom:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(4.f / 7.f, 2.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::bean:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(5.f / 7.f, 2.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::hamburger:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(6.f / 7.f, 2.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::hotdog:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(0.f, 3.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::wiener:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(1.f / 7.f, 3.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::doughnut:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(2.f / 7.f, 3.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::chicken_drumstick:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(3.f / 7.f, 3.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::french_fries:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(4.f / 7.f, 3.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::shrimp_nigiri:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(5.f / 7.f, 3.f / 7.f));
		sprite->changeAnimation(0);
		break;
	case Food::cake:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(6.f / 7.f, 3.f / 7.f));
		sprite->changeAnimation(0);
		break;
	default:
		sprite->setNumberAnimations(1);
		sprite->setAnimationSpeed(0, 8);
		sprite->addKeyframe(0, glm::vec2(6.f / 7.f, 3.f / 7.f));
		sprite->changeAnimation(0);
		break;
	}
}