#pragma once
#include "Animated.h"

class Bubble :
    public Animated
{
public:
    //TODO: Afegir sprite de bubble.
    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht = "images/varied.png") override;

    void update(int deltaTime) override;

    void setVelocity(const glm::ivec2& vel) { velocity = vel; }

private:
    glm::ivec2 velocity = glm::ivec2(1, 1);

};

