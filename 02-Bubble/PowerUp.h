#pragma once
#include "Animated.h"

class PowerUp : 
	public Animated
{
public: 
	enum class Type {
		FREEZE_TIME, 
		DYNAMITE,
		DOUBLE_WIRE, 
		POWER_WIRE,
		VULCAN_MISSILE, 
		INVINCIBILITY,
		SLOW_TIME
	};
	void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, Type tip, const char* sprtsht = "images/varied.png");

	void update(int deltaTime);

	bool isCollected() const { return collected;}

	void onCollision(short flags) override;

	void setType(Type tip);



private:
	Type type;
	bool collected = false;

	int currTime = 0;
	int timeOut = 3000.0f;
};


