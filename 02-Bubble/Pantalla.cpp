#include "Pantalla.h"

#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>



Pantalla::Pantalla()
{
}

Pantalla::~Pantalla()
{
	if (soundEngine != nullptr)
	{
		soundEngine->drop();
		soundEngine = nullptr;
	}
}


void Pantalla::init()
{
	initShaders();
	projection = glm::ortho(0.f, float(SCREEN_WIDTH / SCALING), float(SCREEN_HEIGHT / SCALING), 0.f);
	currentTime = 0.0f;
	soundEngine = irrklang::createIrrKlangDevice();
}

void Pantalla::update(int deltaTime)
{
	currentTime += deltaTime;
}

void Pantalla::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	if(fons != nullptr)
		fons->render();
}

void Pantalla::toggleDebugBoxes()
{
	debugBoxes = !debugBoxes;
}

void Pantalla::clearMem()
{
	if (soundEngine != nullptr)
	{
		soundEngine->drop();
		soundEngine = nullptr;
	}
}

void Pantalla::loadImage(const char* filename)
{
	if (fons != nullptr)
		delete fons;
	fons = new Animated();
	fons->init(glm::ivec2(0, 0), texProgram, filename, glm::ivec2(SCREEN_WIDTH, SCREEN_HEIGHT), glm::vec2(1.0f, 1.0f));
	fons->doGravity(false);
}

void Pantalla::playSound(const char* sound)
{
	soundEngine->play2D(sound);
}

void Pantalla::pauseSound(bool pause)
{
	if (pause)
		soundEngine->setAllSoundsPaused(true);
	else
		soundEngine->setAllSoundsPaused(false);
}

void Pantalla::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}




