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

    for (auto& powerUp : powerUps) {

        if (collidesWithFloor || collidesWithPlayer) {

        }
        else powerUp.moveDown(6.5);
    }

}

bool PowerUp::collidesWithFloor(const TileMap& tileMap) const {
    int tileX = posX / tileMap.getTileSize();
    int tileY = (posY + powerUpHeight) / tileMap.getTileSize();
    
    return tileMap.isFloorTile(tileX, tileY);
}

void PowerUp::moveDown(float gravity) {
    posY += velocity.y;
    velocity.y = gravity;
}


