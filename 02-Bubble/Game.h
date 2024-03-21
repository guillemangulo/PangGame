#ifndef _GAME_INCLUDE
#define _GAME_INCLUDE


#include <GLFW/glfw3.h>
#include "Pantalla.h"
#include "Joc.h"


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

	enum directions
	{
		UP,DOWN,LEFT,RIGHT,UPLEFT,UPRIGHT,DOWNLEFT,DOWNRIGHT,NONE
	};
	enum pantalles
	{
		MAINMENU, GAME, GAMEOVER, TIMEOVER, WIN, CREDITS, CONTROLS, MAPA
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

	directions getDirection() const;

	bool IsShooting() const;


private:
	bool bPlay; // Continue to play game?
	bool keys[GLFW_KEY_LAST+1]; // Store key states so that 
							    // we can have access at any time

	int mouseX, mouseY;
	bool mouse_down = false;

	int level = 1;

	
	Pantalla* scene;

	Joc nivell; 

};


#endif // _GAME_INCLUDE


