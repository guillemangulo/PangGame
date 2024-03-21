#ifndef _PANTALLA_INCLUDE
#define _PANTALLA_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"

class Pantalla
{

public:
	Pantalla();
	~Pantalla();

	virtual void init();
	virtual void update(int deltaTime);
	virtual void render();

private:
	void initShaders();

private:
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
};


#endif // _SCENE_INCLUDE

