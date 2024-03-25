#include "PowerUp.h"

PowerUp::PowerUp(Type type, int x, int y) : type(type), posX(x), posY(y) {}

bool PowerUp::collidesWithFloor(const TileMap& tileMap, int nextY) const {
    int tileX = posX / tileMap.getTileSize();
    int tileY = (posY + nextY) / tileMap.getTileSize();
    
    return tileMap.isFloorTile(tileX, tileY);
}


void PowerUp::update(int deltaTime) {

    moveDown();
    

    //TODO: Collisions with player

    
    //if (collidesWithFloor(tileMap, nextY) || currentTime >= TIMEOUT) collected = true;

}

void PowerUp::moveDown() {

}


// en el update de Joc pasarli TileMap per fer collideswithfloor??
// how to implement movedown