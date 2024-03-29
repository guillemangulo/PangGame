#pragma once
#include "Animated.h"

class Bubble :
    public Animated
{
public:
    //TODO: Afegir sprite de bubble.
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht = "images/bubble.png");

    void update(int deltaTime) override;

    void setVelocity(const glm::ivec2& vel) { velocity = vel; }

private:
    glm::vec2 velocity = glm::vec2(1, 1);
    int cumulatedTime = 0;
    int gravStep = 0;
    int actVelocity = 0;

};

