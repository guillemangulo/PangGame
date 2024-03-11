#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"


void Game::init()
{
	bPlay = true;
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	scene.init();
}

bool Game::update(int deltaTime)
{
	scene.update(deltaTime);

	return bPlay;
}

void Game::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene.render();
}

void Game::keyPressed(int key)
{
	if(key == GLFW_KEY_ESCAPE) // Escape code
		bPlay = false;
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
		scene.teleportPlayer(x-35, y-15);
	}
	mouseX = x;
	mouseY = y;
}

void Game::mousePress(int button)
{
	scene.teleportPlayer(mouseX-35, mouseY-15);
	mouse_down = true;
}

void Game::mouseRelease(int button)
{
	mouse_down = false;
}

bool Game::getKey(int key) const
{
	return keys[key];
}



