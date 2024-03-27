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
	if (soundEngine != nullptr)
	{
		soundEngine->drop();
		soundEngine = nullptr;
	}
}

void Joc::clearMem()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (soundEngine != nullptr)
	{
		soundEngine->drop();
		soundEngine = nullptr;
	}
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

	background = new Animated();
	background->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/BackgroundLvls/L" + std::to_string(nivell) + ".png", glm::ivec2(SCREEN_WIDTH/SCALING, SCREEN_HEIGHT/SCALING - 32));
	background->doGravity(false);


	soundEngine = irrklang::createIrrKlangDevice();
	playLevelSong(nivell);
	
	currentTime = 0.0f;
}

void Joc::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	calculateCollisions();
	for (unsigned int i = 0; i < powerUps.size(); i++)
		powerUps[i]->update(deltaTime);

	for (unsigned int i = 0; i < bubbles.size(); i++)
		bubbles[i]->update(deltaTime);
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

	background->render();
	map->render();
	for (unsigned int i = 0; i < powerUps.size(); i++)
		powerUps[i]->render();

	for (unsigned int i = 0; i < bubbles.size(); i++)
		bubbles[i]->render();

	player->render();

}

void Joc::teleportPlayer(int x, int y)
{
	/*
	std::shared_ptr<Animated> newBubble = std::make_shared<Bubble>();

	if (auto bubble = std::dynamic_pointer_cast<Bubble>(newBubble)) 
	{
		bubble->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram); // "images/PowerUp.png");
		bubble->setPosition(glm::vec2(x / SCALING, y / SCALING));
		bubble->setTileMap(map);
		bubble->setIndex(bubbles.size());
		bubble->setParent(this);
	}
	bubbles.push_back(newBubble);
	//*/
	/*
	std::shared_ptr<Animated> newPU = std::make_shared<PowerUp>();
	if (auto PU = std::dynamic_pointer_cast<PowerUp>(newPU)) {
		PU->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, PowerUp::Type::FREEZE_TIME);// "images/PowerUp.png");
		PU->setPosition(glm::vec2(x / SCALING, y / SCALING));
		PU->setTileMap(map);
		PU->setIndex(powerUps.size());
		PU->setParent(this);
	}
	powerUps.push_back(newPU);//*/

	player->setPosition(glm::vec2(x/SCALING, y / SCALING));
}

void Joc::toggleDebugBoxes()
{
	//player->debugColisionBoxToggle();
	//TODO:map->toggleDebugBoxes();
}

void Joc::playLevelSong(const int level)
{
	if(level==1||level==2||level==3)
	{
		playSound("audio/02Stage01-03.wav");
	}

	else if(level==4||level==5||level==6)
	{
		playSound("audio/03Stage04-06.wav");
	}

	else if(level==7||level==8||level==9||level==40||level==41||level==42)
	{
		playSound("audio/04Stage07-09_40-42.wav");
	}

	else if(level==10||level==11||level==12||level==31||level==32||level==33)
	{
		playSound("audio/05Stage10-12_31-33.wav");
	}

	else if(level==13||level==14||level==15||level==37||level==38||level==39)
	{
		playSound("audio/06Stage13-15_37-39.wav");
	}

	else if(level==16||level==17||level==18||level==34||level==35||level==36)
	{
		playSound("audio/07Stage16-18_34-36.wav");
	}

	else if(level==19||level==20||level==21||level==46||level==47||level==48)
	{
		playSound("audio/08Stage19-21_46-48.wav");
	}

	else if(level==22||level==23||level==24)
	{
		playSound("audio/09Stage22-24.wav");
	}

	else if(level==25||level==26||level==27||level==43||level==44||level==45)
	{
		playSound("audio/10Stage25-27_43-45.wav");
	}

	else if(level==28||level==29||level==30||level==49||level==50||level==51)
	{
		playSound("audio/11Stage28-30_49-50.wav");
	}
}

void Joc::calculateCollisions()
{
	glm::ivec2 playerPos = player->getPosition();
	for(unsigned int i = 0; i < powerUps.size(); i++)
	{
		if (powerUps[i]->shouldCollideWithPlayer())
		{
			glm::ivec2 PUpos = powerUps[i]->getPosition();
			if (playerPos.x < PUpos.x + powerUps[i]->getSize().x &&
				playerPos.x + player->getSize().x > PUpos.x &&
				playerPos.y < PUpos.y + powerUps[i]->getSize().y &&
				playerPos.y + player->getSize().y > PUpos.y)
			{
				powerUps[i]->onCollision(0b1000);
			}
		}
	}
}

void Joc::removePowerUP(int obj)
{
	powerUps.erase(powerUps.begin() + obj);
	for (unsigned int i = 0; i < powerUps.size(); i++)
		powerUps[i]->setIndex(i);
}
