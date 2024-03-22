#ifndef _ANIMATED_INCLUDE
#define _ANIMATED_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "ShaderProgram.h"

#define fallTableSize 4



class Animated
{
	public:
		virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const char* sprtsht);
		virtual void update(int deltaTime);
		void render();

		void setTileMap(TileMap* tileMap);
		void setPosition(const glm::vec2 &_pos);

		bool doGravity(bool gravity);


	protected:

		void fall(int deltaTime);
		glm::ivec2 tileMapDispl, pos;
		bool doGrav;
		bool falling;
		int fallFrame;
		float* fallTable = new float[fallTableSize]{ 0.1f, 0.2f, 0.3f, 0.4f };
		Texture spritesheet;
		Sprite* sprite;
		TileMap* map;
};
#endif // _ANIMATED_INCLUDE


