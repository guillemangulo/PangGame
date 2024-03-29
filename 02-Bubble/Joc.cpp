#include "Joc.h"
#include "Game.h"

#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 20


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
	background->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/BackgroundLvls/L" + std::to_string(nivell) + ".png", glm::ivec2(SCREEN_WIDTH/SCALING, SCREEN_HEIGHT/SCALING - 32), glm::vec2(1.f,1.f));
	background->doGravity(false);

	TextWritter* text = new TextWritter();
	text->writeText("player-1A", glm::vec2(2 * 8, 26 * 8), texProgram);
	text->writeText("player-2A", glm::vec2(36* 8, 26 * 8), texProgram);
	text->writeText(getLevelName(nivell), glm::vec2(19 * 8, 26 * 8), texProgram);
	texts.push_back(text);


	soundEngine = irrklang::createIrrKlangDevice();
	playLevelSong(nivell);


	
	currentTime = 0.0f;
}

void Joc::update(int deltaTime)
{
#define tickRate 1000/50
	currentTime += deltaTime;
	cumulatedTime += deltaTime;
	//Aixó garanteix un tickrate de no més de tickRate hz evitant que es moguin massa ràpid sent una alternativa al deltaTime tradicional
	//que funciona millor amb jocs basats en integers on no podem fer servir decimals.
	while (cumulatedTime > tickRate)
	{
		currentTick++;
		cumulatedTime -= tickRate;
		player->update(tickRate);
		calculateCollisions();
		if (freezeTime > 0)
		{
			freezeTime -= tickRate;
		}
		else
		{
			if (slowTime > 0 && currentTick % 2 == 0)
			{
				slowTime -= tickRate*2;
			}
			else
			{
				for (unsigned int i = 0; i < powerUps.size(); i++)
					powerUps[i]->update(tickRate);

				for (unsigned int i = 0; i < bubbles.size(); i++)
					bubbles[i]->update(tickRate);

				for (unsigned int i = 0; i < menjar.size(); i++)
					menjar[i]->update(tickRate);

			}
		}
	}

	for (unsigned int i = 0; i < cadena.size(); i++)
		cadena[i]->update(tickRate);

	timerCadena += deltaTime;
	if (Game::instance().getKey(GLFW_KEY_F)) {
		glm::ivec2 pos = player->getPosition();
		if (cadena.size() < maxcadenas) {
			if (timerCadena > 100) {
				createCadena(pos.x* SCALING, pos.y* SCALING);
				timerCadena = 0;
			}
		}
	}


}

void Joc::render()
{
	Pantalla::render();

	background->render();
	map->render();

	for (unsigned int i = 0; i < cadena.size(); i++) {
		cadena[i]->render();
	}

	
	for (unsigned int i = 0; i < powerUps.size(); i++)
		powerUps[i]->render();

	for (unsigned int i = 0; i < bubbles.size(); i++)
		bubbles[i]->render();

	for (unsigned int i = 0; i < menjar.size(); i++)
		menjar[i]->render();

	for (unsigned int i = 0; i < texts.size(); i++)
		texts[i]->render();

	
	player->render();

}

void Joc::addPointsJ1(int points)
{
	if (auto nivellpa = dynamic_cast<Player*>(player)) {
		nivellpa->addPoints(points);
	}
}

void Joc::createBubble(int x, int y, int tamany)
{
	std::shared_ptr<Animated> newBubble = std::make_shared<Bubble>();

	if (auto bubble = std::dynamic_pointer_cast<Bubble>(newBubble))
	{
		bubble->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/bubble.png");
		bubble->setPosition(glm::vec2(x / SCALING, y / SCALING));
		bubble->setTileMap(map);
		bubble->setIndex(bubbles.size());
		bubble->setParent(this);
	}
	bubbles.push_back(newBubble);
}

void Joc::createPowerUp(int x, int y, int type)
{
	std::shared_ptr<Animated> newPU = std::make_shared<PowerUp>();
	if (auto PU = std::dynamic_pointer_cast<PowerUp>(newPU)) {
		PU->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, type);// "images/PowerUp.png");
		PU->setPosition(glm::vec2(x / SCALING, y / SCALING));
		PU->setTileMap(map);
		PU->setIndex(powerUps.size());
		PU->setParent(this);
	}
	powerUps.push_back(newPU);
}

void Joc::createFood(int x, int y, int type)
{
	std::shared_ptr<Animated> newPU = std::make_shared<Food>();
	if (auto PU = std::dynamic_pointer_cast<Food>(newPU)) {
		PU->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, type, "images/foods.png");
		PU->setPosition(glm::vec2(x / SCALING, y / SCALING));
		PU->setColisionFlags(0b1101);
		PU->setColSize(glm::ivec2(16, 16));
		PU->setTileMap(map);
		PU->setIndex(menjar.size());
		PU->setParent(this);
	}
	menjar.push_back(newPU);
}

void Joc::createCadena(int x, int y) {
	std::shared_ptr<Animated> newPU = std::make_shared<Cadena>();
	if (auto PU = std::dynamic_pointer_cast<Cadena>(newPU)) {
		PU->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, "images/cadena.png");
		PU->setPosition(glm::vec2(x / SCALING, y / SCALING));
		PU->setColisionFlags(0b1101);
		PU->setColSize(glm::ivec2(16, 16));
		PU->setTileMap(map);
		PU->setIndex(cadena.size());
		PU->setParent(this);
	}
	cadena.push_back(newPU);
}

void Joc::teleportPlayer(int x, int y)
{
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
	for (unsigned int i = 0; i < powerUps.size(); i++)
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
	for (unsigned int i = 0; i < menjar.size(); i++)
	{
		if (menjar[i]->shouldCollideWithPlayer())
		{
			glm::ivec2 PUpos = menjar[i]->getPosition();
			if (playerPos.x < PUpos.x + menjar[i]->getSize().x &&
				playerPos.x + player->getSize().x > PUpos.x &&
				playerPos.y < PUpos.y + menjar[i]->getSize().y &&
				playerPos.y + player->getSize().y > PUpos.y)
			{
				menjar[i]->onCollision(0b1000);
			}
		}
	}

	for (unsigned int i = 0; i < cadena.size(); i++)
	{
		if (auto PU = std::dynamic_pointer_cast<Cadena>(cadena[i])) {
			for (int j = 0; j < bubbles.size(); ++j) {
				bool hihacol = 
					PU->circleRect(bubbles[j]->getPosition().x, bubbles[j]->getPosition().y, bubbles[j]->getSize().x);
				if (hihacol) {
					bubbles[j]->onCollision(0b0100);
					removeCadena(i);
				}
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

char* Joc::getLevelName(int nivell)
{
	if (nivell == 1 || nivell == 2 || nivell == 3)
		return "mt.fujiA";
	else if (nivell == 4 || nivell == 5 || nivell == 6)
		return "mt.keirinA";
	else if (nivell == 7 || nivell == 8 || nivell == 9)
		return "emerald templeA";
	else if (nivell == 10 || nivell == 11 || nivell == 12)
		return "ankor wattA";
	else if (nivell == 13 || nivell == 14 || nivell == 15)
		return "australiaA";
	else if (nivell == 16 || nivell == 17 || nivell == 18)
		return "taj mahalA";
	else if (nivell == 19 || nivell == 20 || nivell == 21)
		return "leningradA";
	else if (nivell == 22 || nivell == 23 || nivell == 24)
		return "parisA";
	else if (nivell == 25 || nivell == 26 || nivell == 27)
		return "londonA";
	else if (nivell == 28 || nivell == 29 || nivell == 30)
		return "barcelonaA";
	else if (nivell == 31 || nivell == 32 || nivell == 33)
		return "athensA";
	else if (nivell == 34 || nivell == 35 || nivell == 36)
		return "egyptA";
	else if (nivell == 37 || nivell == 38 || nivell == 39)
		return "kenyaA";
	else if (nivell == 40 || nivell == 41 || nivell == 42)
		return "new yorkA";
	else if (nivell == 43 || nivell == 44 || nivell == 45)
		return "mayaA";
	else if (nivell == 46 || nivell == 47 || nivell == 48)
		return "antarticaA";
	else if (nivell == 49 || nivell == 50 || nivell == 51)
		return "easter islandA";
	else
		return "errorA";
}

void Joc::removeFood(int obj)
{
	menjar.erase(menjar.begin() + obj);
	for (unsigned int i = 0; i < menjar.size(); i++)
		menjar[i]->setIndex(i);
}

void Joc::removeCadena(int obj) {
	cadena.erase(cadena.begin() + obj);
	for (unsigned int i = 0; i < cadena.size(); i++)
		cadena[i]->setIndex(i);
}
