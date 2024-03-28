#pragma once
#include "Animated.h"
class Food :
    public Animated
{
public:
    enum tipus
    {
        cherries,
        lemon,
        banana,
        orange,
        watermelon,
        pineapple,
        grapes,
        apple,
        strawberry,
        honeydew,
        pickle,
        eggplant,
        tomato,
        squash,
        carrot,
        corn,
        green_pepper,
        radish,
        mushroom,
        bean,
        hamburger,
        hotdog,
        wiener,
        doughnut,
        chicken_drumstick,
        french_fries,
        shrimp_nigiri,
        cake
    };

    void update(int deltaTime) override;

    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, int tip, const char* sprtsht);

    void onCollision(short flags) override;

    int calcularPunts();

    void setTipus(int tipus);

private:
    int type;
    int currTime = 0;
    int timeOut = 5000;
};

