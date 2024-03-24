#pragma once
#include "Pantalla.h"

#include "TileMap.h"
#include "Animated.h"
#include "Player.h"


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

	private:
		TileMap* map;
		Player* player;
};


