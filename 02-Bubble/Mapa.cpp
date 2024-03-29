#include "Mapa.h"
#include "Game.h"

using namespace glm;

void Mapa::init()
{
	Pantalla::init();
	game = &Game::instance();

	background = new Animated();
	background->init(ivec2(0,0),texProgram,"images/map.png",ivec2(SCREEN_WIDTH/SCALING,SCREEN_HEIGHT/SCALING));
	background->doGravity(false);

	cursor = new Animated();
	cursor->init(ivec2(0,0),texProgram,"images/i&w1.png",ivec2(16,16),vec2(0.25f,0.25f));
	cursor->doGravity(false);
	cursor->setColSize(ivec2(16,32));

	cursor->setNumAnims(3);
	cursor->setAnimSpeed(0, 8);
	cursor->setAnimSpeed(1, 32);
	cursor->setAnimSpeed(2, 16);

	#define SPRITE_BLOCK 0.25f

	cursor->addKeyframe(0, vec2(1 * SPRITE_BLOCK, 2* SPRITE_BLOCK));

	cursor->addKeyframe(1, vec2(2 * SPRITE_BLOCK, 2* SPRITE_BLOCK));
	cursor->addKeyframe(1, vec2(3 * SPRITE_BLOCK, 2* SPRITE_BLOCK));
	cursor->addKeyframe(1, vec2(0 * SPRITE_BLOCK, 3* SPRITE_BLOCK));
	cursor->addKeyframe(1, vec2(3 * SPRITE_BLOCK, 2* SPRITE_BLOCK));

	cursor->addKeyframe(2, vec2(1 * SPRITE_BLOCK, 2* SPRITE_BLOCK));
	cursor->addKeyframe(2, vec2(3 * SPRITE_BLOCK, 3* SPRITE_BLOCK));
	cursor->addKeyframe(2, vec2(1 * SPRITE_BLOCK, 2 * SPRITE_BLOCK));
	cursor->addKeyframe(2, vec2(1 * SPRITE_BLOCK, 2 * SPRITE_BLOCK));

	countdown = new Animated();
	countdown->init(ivec2(0,0),texProgram,"images/countdown.png",ivec2(64,64),vec2(1.0f/3.f,1.f/3.f));
	countdown->doGravity(false);
	countdown->setPosition(ivec2(500 / SCALING, 55 / SCALING));

	countdown->setNumAnims(1);
	countdown->setAnimSpeed(0, 1);

	#define SPRITE_BLOCK 0.333333f

	countdown->addKeyframe(0, vec2(2 * SPRITE_BLOCK, 0 * SPRITE_BLOCK));
	countdown->addKeyframe(0, vec2(1 * SPRITE_BLOCK, 0 * SPRITE_BLOCK));
	countdown->addKeyframe(0, vec2(0 * SPRITE_BLOCK, 0 * SPRITE_BLOCK));
	countdown->addKeyframe(0, vec2(2 * SPRITE_BLOCK, 1 * SPRITE_BLOCK));
	countdown->addKeyframe(0, vec2(1 * SPRITE_BLOCK, 1 * SPRITE_BLOCK));
	countdown->addKeyframe(0, vec2(0 * SPRITE_BLOCK, 1 * SPRITE_BLOCK));
	countdown->addKeyframe(0, vec2(2 * SPRITE_BLOCK, 2 * SPRITE_BLOCK));
	countdown->addKeyframe(0, vec2(1 * SPRITE_BLOCK, 2 * SPRITE_BLOCK));
	countdown->addKeyframe(0, vec2(0 * SPRITE_BLOCK, 2 * SPRITE_BLOCK));
	countdown->addKeyframe(0, vec2(0 * SPRITE_BLOCK, 2 * SPRITE_BLOCK));
	countdown->addKeyframe(0, vec2(0 * SPRITE_BLOCK, 2 * SPRITE_BLOCK));

	countdown->setAnimation(0);

	//TODO: Set Countdown
	//TODO: Cursor Anim
	//TODO: Level info

	levelsPosCur = new int[34] {696, 152, 614, 152, 582, 213, 614, 213, 670, 334, 544, 206, 422, 87, 360, 104, 311, 87, 270, 142, 366, 142, 416, 174, 416, 255, 168, 134, 95, 206, 184, 390, 32, 318};

	pos1 = ivec2(696, 152);

	playSound("audio/20Map.wav");
}

void Mapa::update(int deltaTime)
{
	Pantalla::update(deltaTime);
	ivec2 joy = game->getDirection();
	if (joy.x < 0 && currentTime - lastTime > 200)
	{
		lastTime = currentTime;
		level += 1;
	}
	else if (joy.x > 0 && currentTime - lastTime> 200)
	{
		lastTime = currentTime;
		level -= 1;
	}

	if(level < 0)
		level = 0;
	else if(level > 16)
		level = 16;
	
	ivec2 curSize = cursor->getSize()/2;
	ivec2 curPos = ivec2(levelsPosCur[level * 2] / SCALING, levelsPosCur[level * 2 + 1] / SCALING) - curSize;
	if (currentTime < 8500)
		cursor->setPosition(lerp(pos1,curPos,currentTime-lastTime,150));
	else
		cursor->setPosition(curPos);

	background->update(deltaTime);
	cursor->update(deltaTime);
	countdown->update(deltaTime);
	if (currentTime > 8500)
		cursor->setAnimation(2);
	if(currentTime > 10000 || currentTime > 500 &&  (game->getKey(GLFW_KEY_F) || game->getKey(GLFW_KEY_RIGHT_SHIFT) || game->getKey(GLFW_KEY_ENTER)))
	{
		game->setLevel(level*3+1);
		game->loadScreen(Game::GAME);
	}
}

void Mapa::render()
{
	Pantalla::render();
	background->render();
	countdown->render();
	cursor->render();
}

glm::ivec2 Mapa::lerp(glm::ivec2 _pos1, glm::ivec2 _pos2, int currTime, int maxtime)
{
	float t = (float)currTime / maxtime;
	glm::vec2 pos1f = glm::vec2(_pos1.x+(_pos2.x - _pos1.x)*t, _pos1.y+(_pos2.y - _pos1.y) * t);
	cursor->setAnimation(1);
	if (currTime >= maxtime)
	{
		cursor->setAnimation(0);
		pos1 = _pos2;
	}
	return pos1f;
}
