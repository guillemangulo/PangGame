#include <cstdlib>
#include "Player.h"
#include "TileMap.h"


class PowerUp
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
	Type getType() const;
	int getX() const;
	int getY() const;

	bool isActivated() const;
	void activate() { activated = true; }
	void desactivate() { activated = false; }
	void update();
	bool collidesWithFloor(const TileMap& tileMap) const;
	bool collidesWithPlayer() const;

	void moveDown(float gravity);

private:
	Type type;
	int posX;
	int posY;
	bool activated;
	int powerUpHeight = 2; // por ejemplo

	glm::vec2 velocity;
};


