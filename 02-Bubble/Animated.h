#ifndef _ANIMATED_INCLUDE
#define _ANIMATED_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "ShaderProgram.h"

#define fallTableSize 18



class Animated
{
	public:
		virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht);
		virtual void update(int deltaTime);
		void render();

		void setTileMap(TileMap* tileMap);
		void setPosition(const glm::vec2 &_pos);

		void updatePosition();

		bool doGravity(bool gravity);

		void drawColisionBox(glm::ivec2* pos, const glm::ivec2& size, const glm::ivec2& sizeoff = glm::ivec2(1, 1), const glm::ivec2 dir = glm::ivec2(0,0)) const;
		void debugColisionBoxToggle();


	protected:

		void fall(int deltaTime);
		glm::ivec2 tileMapDispl, pos;
		glm::ivec2 size = glm::ivec2(1,1);
		glm::ivec2 sizeoff = glm::ivec2(0, 0);
		bool doGrav = true;
		bool falling = false;
		bool debugColision = false;
		int fallFrame = 0;
		int* fallTable = new int[fallTableSize]{2,0,1,0,1,1,2,1,2,2,2,2,3,2,3,3,3,4};
		Texture spritesheet;
		Sprite* sprite;
		TileMap* map;
};
#endif // _ANIMATED_INCLUDE


