#pragma once
#include "Animated.h"

class Cadena :
    public Animated
{
public:
    bool circleRect(float cx, float cy, float radius);

    void update(int deltaTime) override;

    void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht);
private:

};

