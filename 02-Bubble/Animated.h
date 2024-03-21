#ifndef _ANIMATED_INCLUDE
#define _ANIMATED_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "ShaderProgram.h"



class Animated
{
	public:
		virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht);
		virtual void update(int deltaTime);
		void render();

		void setTileMap(TileMap* tileMap);
		void setPosition(const glm::vec2 &_pos);


	protected:
		glm::ivec2 tileMapDispl, pos;
		Texture spritesheet;
		Sprite* sprite;
		TileMap* map;
};
#endif // _ANIMATED_INCLUDE


