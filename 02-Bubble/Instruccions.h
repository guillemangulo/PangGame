#pragma once
#include "Pantalla.h"
#include "Animated.h"

class Game;
class Instruccions :
    public Pantalla
{
public:
    Instruccions() {};
    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:

    Animated* background;
    Game* game;
    int pag = 1;

};
