#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include <GLFW/glfw3.h>
#include "Pantalla.h"
#include "Joc.h"
#include "Mapa.h"
#include "Menu.h"
#include "Credits.h"
#include "Instruccions.h"

// Game is a singleton (a class with a single instance) that represents our whole application


class Game
{
private:
	Game() {}
	
public:
	static Game &instance()
	{
		static Game G;
		return G;
	}
	enum pantalles
	{
		MAINMENU, GAME, GAMEOVER, TIMEOVER, WIN, CREDITS, CONTROLS, MAPA, INSTRUCTIONS
	};

	void init();
	bool update(int deltaTime);
	void render();
	
	// Input callback methods
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMove(int x, int y);
	void mousePress(int button);
	void mouseRelease(int button);

	void loadScreen(pantalles p);

	bool getKey(int key) const;

	glm::ivec2 getDirection() const;

	bool IsShooting() const;

	void setLevel(int l){level = l;}

	void addPunts(int p) { puntsTot += p; }
	int getPunts() { return puntsTot; }

	void seguentNivell() {
		level += 1;
		if (level > 50)
			loadScreen(WIN);
		loadScreen(GAME);
	};

	void reloadNivell() {
		loadScreen(GAME);
	};

	void setGameOver() {
		loadScreen(GAMEOVER);
	};

	int getLives() {
		return lives;
	};

	void addLives(int l) {
		lives += l;
	};

private:
	bool bPlay; // Continue to play game?
	bool keys[GLFW_KEY_LAST+1]; // Store key states so that 
							    // we can have access at any time

	int mouseX, mouseY;
	bool mouse_down = false;
	bool paused = false;

	int puntsTot = 0;

	int level = 1;
	int lives = 3;

	string debug = "";
	
	Pantalla* activeScene = nullptr;

	Joc nivell; 
	Mapa mapa;
	Menu menu;
	Credits credits;
	Instruccions instruccions;
};


#endif // _GAME_INCLUDE


