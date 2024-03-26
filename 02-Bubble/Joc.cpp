#include "Joc.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 18


Joc::Joc()
{
	map = NULL;
	player = NULL;
}

Joc::~Joc()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}

void Joc::clearMem()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
}

void Joc::init(int nivell)
{
	initShaders();
	map = TileMap::createTileMap("levels/N" + std::to_string(nivell) + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH / SCALING), float(SCREEN_HEIGHT / SCALING), 0.f);

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/PlayerDefault.png");
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	
	currentTime = 0.0f;
}

void Joc::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	calculateCollisions();
	cleanUsedSprites();
	for(int i = 0; i < powerUps.size(); i++)
		powerUps[i]->update(deltaTime);
}

void Joc::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	map->render();
	for (int i = 0; i < powerUps.size(); i++)
		powerUps[i]->render();
	player->render();

}

void Joc::teleportPlayer(int x, int y)
{
	std::shared_ptr<Animated> newPU = std::make_shared<PowerUp>();
	if (auto PU = std::dynamic_pointer_cast<PowerUp>(newPU)) {
		PU->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, PowerUp::Type::FREEZE_TIME);// "images/PowerUp.png");
		PU->setPosition(glm::vec2(x / SCALING, y / SCALING));
		PU->setTileMap(map);
	}
	powerUps.push_back(newPU);
	//player->setPosition(glm::vec2(x/SCALING, y / SCALING));
}

void Joc::toggleDebugBoxes()
{
	//player->debugColisionBoxToggle();
	//TODO:map->toggleDebugBoxes();
}

void Joc::calculateCollisions()
{
	glm::ivec2 playerPos = player->getPosition();
	for each (auto var in powerUps)
	{
		if (var->shouldCollideWithPlayer())
		{
			glm::ivec2 PUpos = var->getPosition();
			if (playerPos.x < PUpos.x + var->getSize().x &&
				playerPos.x + player->getSize().x > PUpos.x &&
				playerPos.y < PUpos.y + var->getSize().y &&
				playerPos.y + player->getSize().y > PUpos.y)
			{
				var->onCollision(0b1000);
			}
		}
	}
}

void Joc::cleanUsedSprites()
{
	for (int i = 0; i < powerUps.size(); i++)
	{
		if (powerUps[i]->isCleanable())
		{
			powerUps.erase(powerUps.begin() + i);
		}
	}
}
