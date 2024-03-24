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

	PowerUp(Type type, int x, int y);


	bool isCollected() const;
	void update(int deltaTime);
	bool collidesWithFloor(const TileMap& tileMap, int nextY) const;

	void moveDown();


private:
	Type type;
	int posX;
	int posY;
	bool collected;
	float currentTime;

	glm::vec2 velocity;

	float TIMEOUT = 3000.0f;
};


