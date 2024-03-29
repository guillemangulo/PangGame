#include "Credits.h"
#include "Game.h"

using namespace glm;

void Credits::init() {
	Pantalla::init();
	game = &Game::instance();

	background = new Animated();
	background->init(ivec2(0, 0), texProgram, "images/credits.png", ivec2(SCREEN_WIDTH / SCALING, SCREEN_HEIGHT / SCALING));
	background->doGravity(false);

}

void Credits::update(int deltaTime) {
	Pantalla::update(deltaTime);
	if (game->getKey(GLFW_KEY_E)) {
		game->loadScreen(Game::MAINMENU);
	}
}

void Credits::render() {
	Pantalla::render();
	background->render();
}