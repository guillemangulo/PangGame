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
	if(!paused)
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

	switch (key)
	{
		case GLFW_KEY_ESCAPE:
		{
			bPlay = false;
			break;
		}
		case GLFW_KEY_1: 
		{
			level = 1;
			loadScreen(GAME);
			break;
		}
		case GLFW_KEY_2:
		{
			level = 2;
			loadScreen(GAME);
			break;
		}
		case GLFW_KEY_3: 
		{
			level = 15;
			loadScreen(GAME);
			break;
		}
		case GLFW_KEY_4:
		{
			level = 4;
			loadScreen(GAME);
			break;
		}
		case GLFW_KEY_KP_ADD:
		{
			level += 1;
			loadScreen(GAME);
			break;
		}
		case GLFW_KEY_KP_SUBTRACT:
		{
			level -= 1;
			loadScreen(GAME);
			break;
		}

		case GLFW_KEY_P:
		{
			paused = !paused;
			if(activeScene != nullptr)
				activeScene->pauseSound(paused);
			break;
		}

		case GLFW_KEY_C:
		{
			activeScene->toggleDebugBoxes();
			break;
		}
		default:
		{
			break;
		}
			
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

		if (activeScene != nullptr)
		{
			activeScene->clearMem();
			activeScene = nullptr;
		}
		nivell = Joc();
		nivell.init(level);
		activeScene = &nivell;
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

glm::ivec2 Game::getDirection() const
{
	//Aixó es pot ampliar per donar suport a més tecles i controladors
	if (keys[GLFW_KEY_UP] || keys[GLFW_KEY_W])
	{
		if(keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_A])
			return glm::ivec2(-1,-1);
		else if(keys[GLFW_KEY_RIGHT] || keys[GLFW_KEY_D])
			return glm::ivec2(1, -1);
		else
			return glm::ivec2(0, -1);;
	}
	else if (keys[GLFW_KEY_DOWN] || keys[GLFW_KEY_S])
	{
		if (keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_A])
			return glm::ivec2(-1, 1);
		else if (keys[GLFW_KEY_RIGHT] || keys[GLFW_KEY_D])
			return glm::ivec2(1, 1);
		else
			return glm::ivec2(0, 1);;
	}
	else if(keys[GLFW_KEY_LEFT] || keys[GLFW_KEY_A])
		return glm::ivec2(-1,0);
	else if(keys[GLFW_KEY_RIGHT] || keys[GLFW_KEY_D])
		return glm::ivec2(1, 0);
	else
		return glm::ivec2(0, 0);
}

bool Game::IsShooting() const
{
	return keys[GLFW_KEY_SPACE];
}

bool Game::getKey(int key) const
{
	return keys[key];
}



