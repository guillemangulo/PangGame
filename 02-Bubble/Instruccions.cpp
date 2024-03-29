#include "Instruccions.h"
#include "Game.h"

using namespace glm;

void Instruccions::init() {
	Pantalla::init();
	game = &Game::instance();

	background = new Animated();
	background->init(ivec2(0, 0), texProgram, "images/instr1.png", ivec2(SCREEN_WIDTH / SCALING, SCREEN_HEIGHT / SCALING));
	background->doGravity(false);

}

void Instruccions::update(int deltaTime) {
	Pantalla::update(deltaTime);

	if (pag == 1 && game->getKey(GLFW_KEY_RIGHT)) {
		pag = 2;
		background->init(ivec2(0, 0), texProgram, "images/instr2.png", ivec2(SCREEN_WIDTH / SCALING, SCREEN_HEIGHT / SCALING));
	}

	if (pag == 2 && game->getKey(GLFW_KEY_LEFT)) {
		pag = 1;
		background->init(ivec2(0, 0), texProgram, "images/instr1.png", ivec2(SCREEN_WIDTH / SCALING, SCREEN_HEIGHT / SCALING));
	}
	
	if (game->getKey(GLFW_KEY_E)) {
		game->loadScreen(Game::MAINMENU);
	}
}

void Instruccions::render() {
	Pantalla::render();
	background->render();
}