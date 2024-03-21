#include "Pantalla.h"

#include "TileMap.h"
#include "Player.h"

class Joc :
    public Pantalla
{
    public:
	Joc();
	~Joc();

	void init(int nivell);
	void update(int deltaTime);
	void render();
	void teleportPlayer(int x, int y);

	private:
		

	private:
		TileMap* map;
		TileMap* foreground;
		TileMap* background;
		Player* player;
};


