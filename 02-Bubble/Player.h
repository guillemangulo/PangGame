#pragma once

#include "Animated.h"


class Player : 
	public Animated
{
	public:
		void init(const glm::ivec2 &tileMapPos, ShaderProgram& shaderProgram,
			const std::string sprtsht = "images/PlayerDefault.png",
			const glm::ivec2 tamany = glm::ivec2(32, 32),
			const glm::vec2 spriteBlock = glm::vec2(1.0f, 1.0f)) override;
		void update(int deltaTime); 
		void addPoints(int p) { points += p; };
		int getPoints() { return points; };
		//*/
	private:

		int points = 0;
		float speed = 2.0f;
		bool escalant = false;
		enum PlayerAnims
		{
			STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, SHOOT, CLIMB_UP, CLIMB_DOWN, TAKE_DAMAGE, END_CLIMB
		};
};


