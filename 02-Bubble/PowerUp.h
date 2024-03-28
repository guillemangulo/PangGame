#pragma once
#include "Animated.h"

class PowerUp : 
	public Animated
{
public: 
	enum type {
		FREEZE_TIME, 
		DYNAMITE,
		DOUBLE_WIRE, 
		POWER_WIRE,
		VULCAN_MISSILE, 
		INVINCIBILITY,
		SLOW_TIME
	};
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int tip, const char* sprtsht = "images/varied.png");

	void update(int deltaTime);

	void PowerUp::actPowerUp();

	bool isCollected() const { return collected;}

	void onCollision(short flags) override;

	void setType(int tip);



private:
	int type;
	bool collected = false;

	int currTime = 0;
	int timeOut = 30000;
};


