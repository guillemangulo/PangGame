#pragma once
#include "Pantalla.h"

#include "TileMap.h"
#include "Animated.h"
#include "Player.h"
#include "PowerUp.h"
#include "Bubble.h"
#include "Food.h"
#include <memory>
#include <vector>


class Joc :
	public Pantalla
{
public:
	Joc();
	~Joc();

	void clearMem();

	void init(int nivell);
	void update(int deltaTime) override;
	void render() override;
	void addPointsJ1(int points);
	void createBubble(int x, int y, int tamany = 0);
	void createFood(int x, int y, int type);
	void createPowerUp(int x, int y, int type);
	void teleportPlayer(int x, int y);
	void toggleDebugBoxes() override;

	void playLevelSong(const int nivell);

	void slowTimePowerUp(int time) { slowTime = time; }
	void freezeTimePowerUp(int time) { freezeTime = time; }

	void calculateCollisions();
	void removePowerUP(int obj);

	void removeFood(int obj);

private:
	TileMap* map;
	Animated* player;
	Animated* background;

	int cumulatedTime = 0;
	unsigned int currentTick = 0;

	int slowTime = 0;
	int freezeTime = 0;


	std::vector<std::shared_ptr<Animated>> powerUps;
	std::vector<std::shared_ptr<Animated>> bubbles;
	std::vector<std::shared_ptr<Animated>> menjar;

};
