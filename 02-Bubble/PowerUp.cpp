#include "PowerUp.h"

PowerUp::PowerUp(Type type, int x, int y) : type(type), posX(x), posY(y) {}

PowerUp::Type PowerUp::getType() const {
    return type;
}

int PowerUp::getX() const {
    return posX;
}

int PowerUp::getY() const {
    return posY;
}

bool PowerUp::isActivated() const {
    return activated;
}

void PowerUp::activate() {
    activated = true;
}

void PowerUp::desactivate() {
    activated = false;
}


void PowerUp::update() {

    fall(0.0f);

}

bool PowerUp::collidesWithFloor(const TileMap& tileMap) const {
    int tileX = posX / tileMap.getTileSize();
    int tileY = (posY + powerUpHeight) / tileMap.getTileSize();
    
    return tileMap.isFloorTile(tileX, tileY);
}

bool PowerUp::collidesWithPlayer() const
{
    return false;
}


