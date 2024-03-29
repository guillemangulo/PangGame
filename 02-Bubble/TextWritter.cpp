#include "TextWritter.h"

glm::vec2 TextWritter::charToPos(char a)
{
	switch (a)
	{
	case 'a':
	{
		return glm::vec2(3.0f, 2.0f);
	}
	case 'b':
	{
		return glm::vec2(4.0f, 2.0f);
	}
	case 'c':
	{
		return glm::vec2(5.0f, 2.0f);
	}
	case 'd':
	{
		return glm::vec2(6.0f, 2.0f);
	}
	case ' ':
	{
		return glm::vec2(0.0f, 0.0f);
	}
	case 'e':
	{
		return glm::vec2(7.0f, 2.0f);
	}
	case 'f':
	{
		return glm::vec2(8.0f, 2.0f);
	}

	case 'g':
	{
		return glm::vec2(9.0f, 2.0f);
	}
	case 'h':
	{
		return glm::vec2(10.0f, 2.0f);
	}
	case 'i':
	{
		return glm::vec2(11.0f, 2.0f);
	}

	case 'j':
	{
		return glm::vec2(12.0f, 2.0f);
	}
	case 'k':
	{
		return glm::vec2(13.0f, 2.0f);
	}

	case 'l':
	{
		return glm::vec2(14.0f, 2.0f);
	}
	case 'm':
	{
		return glm::vec2(0.0f, 3.0f);
	}
	case 'n':
	{
		return glm::vec2(1.0f, 3.0f);
	}
	case 'o':
	{
		return glm::vec2(2.0f, 3.0f);
	}
	case 'p':
	{
		return glm::vec2(3.0f, 3.0f);
	}
	case 'q':
	{
		return glm::vec2(4.0f, 3.0f);
	}
	case 'r':
	{
		return glm::vec2(5.0f, 3.0f);
	}
	case 's':
	{
		return glm::vec2(6.0f, 3.0f);
	}

	case 't':
	{
		return glm::vec2(7.0f, 3.0f);
	}
	case 'u':
	{
		return glm::vec2(8.0f, 3.0f);
	}

	case 'v':
	{
		return glm::vec2(9.0f, 3.0f);
	}

	case 'w':
	{
		return glm::vec2(10.0f, 3.0f);
	}

	case 'x':
	{
		return glm::vec2(11.0f, 3.0f);
	}
	case 'y':
	{
		return glm::vec2(12.0f, 3.0f);
	}

	case 'z':
	{
		return glm::vec2(13.0f, 3.0f);
	}
	case '[':
	{
		return glm::vec2(14.0f, 3.0f);
	}

	case '\\':
	{
		return glm::vec2(0.0f, 4.0f);
	}
	case ']':
	{
		return glm::vec2(1.0f, 4.0f);
	}
	case '^':
	{
		return glm::vec2(2.0f, 4.0f);
	}
	case '_':
	{
		return glm::vec2(3.0f, 4.0f);
	}
	case '/':
	{
		return glm::vec2(0.0f, 1.0f);
	}

	case '0':
	{
		return glm::vec2(1.0f, 1.0f);
	}
	case '1':
	{
		return glm::vec2(2.0f, 1.0f);
	}

	case '2':
	{
		return glm::vec2(3.0f, 1.0f);
	}
	case '3':
	{
		return glm::vec2(4.0f, 1.0f);
	}
	case '4':
	{
		return glm::vec2(5.0f, 1.0f);
	}
	case '5':
	{
		return glm::vec2(6.0f, 1.0f);
	}
	case '6':
	{
		return glm::vec2(7.0f, 1.0f);
	}
	case '7':
	{
		return glm::vec2(8.0f, 1.0f);
	}
	case '8':
	{
		return glm::vec2(9.0f, 1.0f);
	}
	case '9':
	{
		return glm::vec2(10.0f, 1.0f);
	}

	case ':':
	{
		return glm::vec2(11.0f, 1.0f);
	}
	case ';':
	{
		return glm::vec2(12.0f, 1.0f);
	}
	case '<':
	{
		return glm::vec2(13.0f, 1.0f);
	}
	case '=':
	{
		return glm::vec2(14.0f, 1.0f);
	}

	case '!':
	{
		return glm::vec2(1.0f, 0.0f);
	}
	case '"':
	{
		return glm::vec2(2.0f, 0.0f);
	}
	case '#':
	{
		return glm::vec2(3.0f, 0.0f);
	}
	case '$':
	{
		return glm::vec2(4.0f, 0.0f);
	}
	case '%':
	{
		return glm::vec2(5.0f, 0.0f);
	}
	case '&':
	{
		return glm::vec2(6.0f, 0.0f);
	}
	case '\'':
	{
		return glm::vec2(7.0f, 0.0f);
	}

	case '(':
	{
		return glm::vec2(8.0f, 0.0f);
	}
	case ')':
	{
		return glm::vec2(9.0f, 0.0f);
	}
	case '*':
	{
		return glm::vec2(10.0f, 0.0f);
	}
	case '+':
	{
		return glm::vec2(11.0f, 0.0f);
	}
	case ',':
	{
		return glm::vec2(12.0f, 0.0f);
	}
	case '-':
	{
		return glm::vec2(13.0f, 0.0f);
	}
	case '.':
	{
		return glm::vec2(14.0f, 0.0f);
	}
	case '{':
	{
		return glm::vec2(1.0f, 6.0f);
	}
	case '|':
	{
		return glm::vec2(2.0f, 6.0f);
	}
	case '}':
	{
		return glm::vec2(3.0f, 6.0f);
	}
	case '~':
	{
		return glm::vec2(4.0f, 6.0f);
	}

	default:
		break;
	}
}

void TextWritter::writeText(const char* text, glm::vec2 pos, ShaderProgram& program)
{
	changed = true;
	glm::ivec2 size = glm::ivec2(10,10);
	glm::vec2 blockSize = glm::vec2(1.f / 15.f, 1.f / 8.f);
	position = pos;
	for (int i = 0; text[i] != 'A'; i++)
	{
		Animated* letter = new Animated();
		letter->init(glm::vec2(0.0f, 0.0f), program, "images/text.png", size ,blockSize);
		letter->setPosition(pos+glm::vec2(i*(size.x*.9),0));
		letter->setNumAnims(1);
		letter->setAnimSpeed(0,1);
		glm::vec2 charPos = charToPos(text[i]);
		letter->addKeyframe(0, glm::vec2(charPos.x*blockSize.x, charPos.y * blockSize.y));
		letter->setAnimation(0);
		letters.push_back(letter);
		position.x += charSize.x;
	}
}

void TextWritter::render()
{
	for each (Animated * var in letters)
	{
		var->render();
	}
}