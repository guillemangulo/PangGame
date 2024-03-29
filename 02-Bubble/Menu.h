#pragma once
#include "Pantalla.h"
#include "Animated.h"


class Game;

class Menu :
    public Pantalla
{
public:
    Menu() {};
    void init() override;
    void update(int deltaTime) override;
    void render() override;

private:
    
    Animated* background;
    Animated* cursor;
    Game* game;
    int next_selected = 7;
    int count = 0;
    int selection = 0;
    glm::ivec2 pos1;

};


