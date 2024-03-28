#pragma once
#include "Pantalla.h"
#include "Animated.h"

class Game;

class Mapa :
    public Pantalla
{
public:
    Mapa() {};
    void init() override;
    void update(int deltaTime) override;
    void render() override;

    glm::ivec2 lerp(glm::ivec2 pos1, glm::ivec2 pos2, int currTime, int maxtime = 200);
private:
    int level = 0;
    int* levelsPosCur;
    Animated* background;
    Animated* cursor;
    Animated* countdown;
    Game* game;

    int lastTime = 0;

    glm::ivec2 pos1;
};

