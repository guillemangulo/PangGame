#include "Cadena.h"
#include "Joc.h"

void Cadena::init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht) {
    spritesheet.loadFromFile(sprtsht, TEXTURE_PIXEL_FORMAT_RGBA);
    tileMapDispl = tileMapPos;
    sprite = Sprite::createSprite(glm::ivec2(20, 200), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);
    sprite->setPosition(glm::vec2(float(tileMapDispl.x + pos.x), float(tileMapDispl.y + pos.y)));
    setColisionFlags(0b0010);

    setColSize(glm::ivec2(4, 8));
    sizeoff = glm::ivec2(8,8);

    doGravity(false);
}

void Cadena::update(int deltaTime) {
   // Animated::update(deltaTime);
    glm::ivec2 dir;
    dir.y = -1;
    short col = map->collisionMove(&pos, size, sizeoff, dir);
    updatePosition();

    // si hi ha colisio
    if (col != 0) joc->removeCadena(index);
}


// CIRCLE/RECTANGLE
bool Cadena::circleRect(float cx, float cy, float radius) {

    // temporary variables to set edges for testing
    float testX = cx;
    float testY = cy;

    float rx = pos.x + 5;
    float ry = pos.y;
    float rw = 10;
    float rh = 200;


    // which edge is closest?
    if (cx < rx)         testX = rx;      // test left edge
    else if (cx > rx + rw) testX = rx + rw;   // right edge
    if (cy < ry)         testY = ry;      // top edge
    else if (cy > ry + rh) testY = ry + rh;   // bottom edge

    // get distance from closest edges
    float distX = cx - testX;
    float distY = cy - testY;
    float distance = sqrt((distX * distX) + (distY * distY));

    // if the distance is less than the radius, collision!
    if (distance <= radius) {
        return true;
    }
    return false;
}


