#ifndef _ANIMATED_INCLUDE
#define _ANIMATED_INCLUDE

#include "Sprite.h"
#include "TileMap.h"
#include "ShaderProgram.h"
#include <vector>
#include <functional>

#define fallTableSize 18

class Joc;

class Animated
{
public:
	virtual void init(const glm::ivec2& tileMapPos, ShaderProgram& shaderProgram, const std::string sprtsht = "images/varied.png", const glm::ivec2 tamany = glm::ivec2(32, 32));
	virtual void update(int deltaTime);

	/// <summary>
	/// Indica que l'objecte ha col·lisionat. Les flags funcionen tal que:
	/// 0b0001 -> Colisio amb el terra inferior.
	/// 0b0010 -> Colisio amb el tilemap.
	/// 0b0100 -> Colisio amb els dispars.
	/// 0b1000 -> Colisio amb el jugador.
	/// </summary>
	/// <param name="flags">Tipus de colisió</param>
	virtual void onCollision(short flags);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& _pos);

	/// <summary>
	/// Actualitza la posició del sprite del objecte, cridar després de moure.
	/// </summary>
	void updatePosition();

	/// <summary>
	/// Pausa l'objecte. Si no es passa cap parametre, alterna l'estat de pausa.
	/// </summary>
	/// <param name="pausa">Si l'objecte ha d'estar pausat o no.</param>
	/// <returns>L'estat de pausa actual.</returns>
	bool pausa(bool pausa = NULL);

	/// <summary>
	/// Defineix les colisions flags de l'objecte. Les flags funcionen tal que:
	/// 0b0001 -> Colisio amb el terra inferior.
	/// 0b0010 -> Colisio amb el tilemap.
	/// 0b0100 -> Colisio amb els dispars.
	/// 0b1000 -> Colisio amb el jugador.
	/// </summary>
	/// <param name="flags"></param>
	void setColisionFlags(short flags);

	/// <summary>
	/// Defineix si l'objecte ha d'estar afectat per la gravetat o no
	/// </summary>
	/// <param name="gravity">Boolea de si está afectat</param>
	/// <returns>Retorna si l'objecte te gravetat</returns>
	bool doGravity(bool gravity = NULL);

	bool shouldCollideWithPlayer() const { return (colisionFlags & 0b1000) == 0b1000; }
	bool shouldCollideWithDispars() const { return (colisionFlags & 0b0100) == 0b0100; }

	void setParent(Joc* _joc) { this->joc = _joc; }

	void setIndex(int i) { index = i; }

	glm::ivec2 getPosition() const { return pos; }
	glm::ivec2 getSize() const { return size; }
	void setColSize(const glm::ivec2& _size) { size = _size; }
		/*
		void drawColisionBox(glm::ivec2* pos, const glm::ivec2& size, const glm::ivec2& sizeoff = glm::ivec2(1, 1), const glm::ivec2 dir = glm::ivec2(0,0)) const;
		void debugColisionBoxToggle();//*/



	protected:
		//Config params del animated
		glm::ivec2 size = glm::ivec2(1,1);
		glm::ivec2 sizeoff = glm::ivec2(0, 0);
		bool doGrav = true;
		bool paused = false;
		/// <summary>
		/// Flags que indica amb quins elements colisiona l'objecte. No actualitzar directament, utilitzar setColisionFlags.
		/// 0b0001 -> Colisio amb el terra inferior.
		/// 0b0010 -> Colisio amb el tilemap.
		/// 0b0100 -> Colisio amb els dispars.
		/// 0b1000 -> Colisio amb el jugador.
		/// Els valors es poden combinar amb un OR(|).
		/// </summary>
		short colisionFlags = 0b0001;

		/// <summary>
		/// Actualitza l'estat de caiguda de l'objecte.
		/// </summary>
		/// <param name="col">Short amb les flags de col·lisió. Això ho retorna el TileMap i es diferent a les collisionFlags.</param>
		/// <param name="deltaTime">Deprecated</param>
		void fallStateUpdate(short col, int deltaTime = 0);
		glm::ivec2 tileMapDispl, pos;

		Joc* joc;
		int index = NULL;

		bool falling = false;
		bool debugColision = false;
		int fallFrame = 0;
		int* fallTable = new int[fallTableSize]{2,0,1,0,1,1,2,1,2,2,2,2,3,2,3,3,3,4};
		Texture spritesheet;
		Sprite* sprite;
		TileMap* map;
};
#endif // _ANIMATED_INCLUDE


