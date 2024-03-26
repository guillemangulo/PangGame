#pragma once

#include "Animated.h"


class Player : 
	public Animated
{
	public:
		void init(const glm::ivec2 &tileMapPos, ShaderProgram& shaderProgram,const char* sprtsht = "images/PlayerDefault.png");
		void update(int deltaTime);
		//*/
	private:
		float speed = 2.0f;
		enum PlayerAnims
		{
			STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, SHOOT, CLIMB_UP, CLIMB_DOWN, TAKE_DAMAGE, END_CLIMB
		};
};


