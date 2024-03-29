#include "Menu.h"
#include "Game.h"

using namespace glm;

void Menu::init() {
	Pantalla::init();
	game = &Game::instance();
	background = new Animated();
	background->init(ivec2(0, 0), texProgram, "images/menu.png", ivec2(SCREEN_WIDTH / SCALING, SCREEN_HEIGHT / SCALING));
	background->doGravity(false);

	cursor = new Animated();
	cursor->init(ivec2(0, 0), texProgram, "images/selection.png", ivec2(20, 20), vec2(1.f, 1.f));
	cursor->doGravity(false);
	

	playSound("audio/18NameEntry.wav");
}

void Menu::update(int deltaTime) {
	Pantalla::update(deltaTime);
	count += deltaTime;

	if (next_selected == Game::MAPA) {
		if (game->getKey(GLFW_KEY_DOWN)) {
			if (count > 200) {
				count = 0;
				next_selected = Game::INSTRUCTIONS;
				selection += 70;
			}
		}
	}

	if (next_selected == Game::INSTRUCTIONS) {
		if (game->getKey(GLFW_KEY_DOWN)) {
			if (count > 200) {
				count = 0;
				next_selected = Game::CREDITS;
				selection += 70;
			}
		}
		else if (game->getKey(GLFW_KEY_UP)) {
			if (count > 200) {
				count = 0;
				next_selected = Game::MAPA;
				selection -= 70;
			}
		}
	}

	if (next_selected == Game::CREDITS) {
		if (game->getKey(GLFW_KEY_UP)) {
			if (count > 200) {
				count = 0;
				next_selected = Game::INSTRUCTIONS;
				selection -= 70;
			}
		}
	}
		
	if (game->getKey(GLFW_KEY_ENTER)) {
		if (next_selected == 8) game->loadScreen(Game::INSTRUCTIONS);
		else if (next_selected == 5) game->loadScreen(Game::CREDITS);
		else if (next_selected == 7) game->loadScreen(Game::MAPA);
	}

	cursor->setPosition(ivec2(45 / SCALING, (175 + selection) / SCALING));
	background->update(deltaTime);
	cursor->update(deltaTime);
}

void Menu::render() {
	Pantalla::render();
	background->render();
	cursor->render();
}
