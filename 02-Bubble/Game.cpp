#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"


void Game::init()
{
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	loadScreen(MAINMENU);
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
			if(level > 50)
				level = 50;
			loadScreen(GAME);
			break;
		}
		case GLFW_KEY_KP_SUBTRACT:
		{
			level -= 1;
			if(level < 1)
				level = 1;
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

		case GLFW_KEY_M:
		{
			loadScreen(MAPA);
			break;
		}

		case GLFW_KEY_B:
		{
			if (Joc* nivellpa = dynamic_cast<Joc*>(activeScene)) {
				nivellpa->createBubble(mouseX, mouseY);
			}
			break;
		}
		case GLFW_KEY_U:
		{
			if (Joc* nivellpa = dynamic_cast<Joc*>(activeScene)) {
				nivellpa->createPowerUp(mouseX, mouseY,0);
			}
			break;
		}
		case GLFW_KEY_I:
		{
			if (Joc* nivellpa = dynamic_cast<Joc*>(activeScene)) {
				nivellpa->createPowerUp(mouseX, mouseY,6);
			}
			break;
		}

		case GLFW_KEY_O:
		{
			if (Joc* nivellpa = dynamic_cast<Joc*>(activeScene)) {
				nivellpa->createPowerUp(mouseX, mouseY, 2);
			}
			break;
		}
		case GLFW_KEY_T:
		{
			if (Joc* nivellpa = dynamic_cast<Joc*>(activeScene)) {
				nivellpa->teleportPlayer(mouseX, mouseY);
			}
			break;
		}
		case GLFW_KEY_X:
		{
			if (Joc* nivellpa = dynamic_cast<Joc*>(activeScene)) {
				nivellpa->createFood(mouseX, mouseY, (level-1 < 29) ? level-1 : 28);
			}
			break;
		}
		case GLFW_KEY_S:
			activeScene->pauseSound(true);
			break;

		case GLFW_KEY_A:
			activeScene->pauseSound(false);
			break;

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
	mouseX = x;
	mouseY = y;
}

void Game::mousePress(int button)
{
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
		if (activeScene != nullptr)
		{
			activeScene->clearMem();
			activeScene = nullptr;
		}
		menu = Menu();
		menu.init();
		activeScene = &menu;
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
		if (activeScene != nullptr)
		{
			activeScene->clearMem();
			activeScene = nullptr;
		}
		activeScene = new Pantalla();
		activeScene->init();
		activeScene->loadImage("images/gameover.png");
		activeScene->playSound("audio/19GameOver.wav");
		break;
	case Game::TIMEOVER:
		break;
	case Game::WIN:
		if (activeScene != nullptr)
		{
			activeScene->clearMem();
			activeScene = nullptr;
		}
		activeScene = new Pantalla();
		activeScene->init();
		activeScene->loadImage("images/win.png");
		activeScene->playSound("audio/13Ending.wav");
		break;
	case Game::CREDITS:
		if (activeScene != nullptr)
		{
			activeScene->clearMem();
			activeScene = nullptr;
		}
		credits = Credits();
		credits.init();
		activeScene = &credits;
		break;
	case Game::CONTROLS:
		break;
	case Game::MAPA:
		if (activeScene != nullptr)
		{
			activeScene->clearMem();
			activeScene = nullptr;
		}
		mapa = Mapa();
		mapa.init();
		activeScene = &mapa;
		break;
	case Game::INSTRUCTIONS:
		if (activeScene != nullptr)
		{
			activeScene->clearMem();
			activeScene = nullptr;
		}
		instruccions = Instruccions();
		instruccions.init();
		activeScene = &instruccions;
		break;

	default:
		break;
	}
}

glm::ivec2 Game::getDirection() const
{
	//Aix� es pot ampliar per donar suport a m�s tecles i controladors
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



