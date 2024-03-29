#pragma once
#include "Pantalla.h"
#include "Animated.h"

class Game;
class Credits :
    public Pantalla
{
public:
    Credits() {};
    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:

    Animated* background;
    Game* game;
 

};







