#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"


void Game::init()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	level = 30;
	loadScreen(GAME);
	bPlay = true;
}

bool Game::update(int deltaTime)
{
	activeScene->update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	activeScene->render();
}

void Game::keyPressed(int key)
{
	if (key == GLFW_KEY_ESCAPE) // Escape code
		bPlay = false;
	if (key == GLFW_KEY_1) // Escape code
	{
		level = 1;
		loadScreen(GAME);
	}
	if (key == GLFW_KEY_2) // Escape code
	{
		level = 2;
		loadScreen(GAME);
	}

	keys[key] = true;
}

void Game::keyReleased(int key)
{
	keys[key] = false;
}

void Game::mouseMove(int x, int y)
{
	if (mouse_down)
	{
		if (Joc* nivellpa = dynamic_cast<Joc*>(activeScene)) {
			nivellpa->teleportPlayer(mouseX, mouseY);
		}
	}
	mouseX = x;
	mouseY = y;
}

void Game::mousePress(int button)
{

	if (Joc* nivellpa = dynamic_cast<Joc*>(activeScene)) {
		nivellpa->teleportPlayer(mouseX, mouseY);
	}
	mouse_down = true;
}

void Game::mouseRelease(int button)
{
	mouse_down = false;
}

void Game::loadScreen(pantalles p)
{
	switch(p)
	{
	case Game::MAINMENU:

		break;
	case Game::GAME:
	{
		nivell = Joc();
		activeScene = &nivell;
		nivell.init(level);
		break;
	}
	case Game::GAMEOVER:
		break;
	case Game::TIMEOVER:
		break;
	case Game::WIN:
		break;
	case Game::CREDITS:
		break;
	case Game::CONTROLS:
		break;
	case Game::MAPA:
		break;
	default:
		break;
	}
}

Game::directions Game::getDirection() const
{
	//Aixó es pot ampliar per donar suport a més tecles i controladors
	if (keys[GLFW_KEY_UP] || keys[GLFW_KEY_W])
	{
		if(keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_A])
			return UPLEFT;
		else if(keys[GLFW_KEY_RIGHT] || keys[GLFW_KEY_D])
			return UPRIGHT;
		else
			return UP;
	}
	else if (keys[GLFW_KEY_DOWN] || keys[GLFW_KEY_S])
	{
		if(keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_A])
			return DOWNLEFT;
		else if(keys[GLFW_KEY_RIGHT] || keys[GLFW_KEY_D])
			return DOWNRIGHT;
		else
			return DOWN;
	}
	else if(keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_A])
		return LEFT;
	else if(keys[GLFW_KEY_RIGHT] || keys[GLFW_KEY_D])
		return RIGHT;
	else
		return NONE;
}

bool Game::IsShooting() const
{
	return keys[GLFW_KEY_SPACE];
}

bool Game::getKey(int key) const
{
	return keys[key];
}



