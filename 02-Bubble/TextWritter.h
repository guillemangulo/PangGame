#pragma once
#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"
#include "Animated.h"
#include <vector>


class TextWritter
{
public:
	void writeText(const char* text, glm::vec2 pos, ShaderProgram& program);
	glm::vec2 charToPos(char a);
	void render();

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;

	bool changed = false;

	vector<Animated*> letters;

	glm::vec2 charSize = glm::vec2(8.0f / 8.0f, 8.0f / 8.0f);
	Texture fontTexture;
	int nChars;
	glm::vec2 position, tilesheetSize;
};




