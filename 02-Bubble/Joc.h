#pragma once
#include "Pantalla.h"

#include "TileMap.h"
#include "Animated.h"
#include "Player.h"
#include "PowerUp.h"
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
	void teleportPlayer(int x, int y);	
	void toggleDebugBoxes() override;

	void calculateCollisions();
	void cleanUsedSprites();

	private:
		TileMap* map;
		Animated* player;

		std::vector<std::shared_ptr<Animated>> powerUps;
};


