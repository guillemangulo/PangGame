#ifndef _PANTALLA_INCLUDE
#define _PANTALLA_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"

#define SCALING 2

#define SCREEN_WIDTH (48*8+64)*SCALING
#define SCREEN_HEIGHT (26*8+32)*SCALING

class Pantalla
{

public:
	Pantalla();
	~Pantalla();

	virtual void init();
	virtual void update(int deltaTime);
	virtual void render();

protected:
	void initShaders();

	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
};


#endif // _PANTALLA_INCLUDE

