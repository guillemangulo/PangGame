#pragma once
#include "Pantalla.h"

#include "TileMap.h"
#include "Player.h"

#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

class Joc :
    public Pantalla
{
    public:
	Joc();
	~Joc();

	void init(int nivell);
	void update(int deltaTime) override;
	void render() override;
	void teleportPlayer(int x, int y);		

	private:
		TileMap* map;
		TileMap* foreground;
		TileMap* background;
		Player* player;
};


