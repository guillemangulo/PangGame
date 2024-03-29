#pragma once
#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Animated.h"
#include <vector>
#include <string>


class TextWritter
{
public:
	void writeText(string text, glm::vec2 pos, ShaderProgram& program);
	glm::vec2 charToPos(char a);
	void render();
	void centerText();
	void changeText(string text);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;

	vector<Animated*> letters;
	ShaderProgram program;

	glm::vec2 blockSize = glm::vec2(1.f / 15.f, 1.f / 8.f);

	string text;

	glm::ivec2 charSize = glm::ivec2(10,10);
	int nChars;
	glm::vec2 position, tilesheetSize;
};




