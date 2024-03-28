#ifndef _PANTALLA_INCLUDE
#define _PANTALLA_INCLUDE

#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <irrKlang.h>

#include <glm/glm.hpp>
#include "ShaderProgram.h"

#define SCALING 2

#define SCREEN_WIDTH (384)*SCALING
#define SCREEN_HEIGHT (208+32)*SCALING



class Pantalla
{

public:
	Pantalla();
	~Pantalla();

	virtual void init();
	virtual void update(int deltaTime);
	virtual void render();
	virtual void toggleDebugBoxes();
	virtual void clearMem();

	void playSound(const char* sound);
	void pauseSound(bool pause);

protected:
	void initShaders();

	irrklang::ISoundEngine* soundEngine = nullptr;

	bool debugBoxes = false;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
};


#endif // _PANTALLA_INCLUDE

