#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

private:
	TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);


public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap* createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program);

	~TileMap();

	void render() const;
	void free();

	int getTileSize() const { return tileSize; }
	glm::ivec2 getMapSize() const { return mapSize; }

	/// <summary>
	/// collisionMove mira si hi ha colisio amb la pos més la dir per una capsa de size i aplica aquest moviment al vector pos.
	/// Les colisions no son elastiques i deixarán l'objecte just a la vora del bloc.
	/// </summary>
	/// <param name="pos">Punter a la posició actual del objecte</param>
	/// <param name="size">Escala de la caixa de colisions</param>
	/// <param name="dir">Cantitat de moviment a intentar</param>
	/// <returns>Retorna el short de colisions com a un bitmap de +x -x +y -y en els bits menys significatius.</returns>
	short collisionMove(glm::ivec2* pos, const glm::ivec2& size, const glm::ivec2& sizeoff = glm::ivec2(0, 0) , const glm::ivec2 dir = glm::ivec2(0,0)) const;

	/// <summary>
	/// Calcula les colisions amb una esfera de radi bubbleRadius i posicio bubblePosition amb el tilemap.
	/// </summary>
	/// <param name="bubbleRadius">Radi en pixels de la bombolla</param>
	/// <param name="bubblePosition">Posició en pixels del centre de la bombolla.</param>
	/// <returns>Normal de la col·lisió amb la cel·la.</returns>
	glm::ivec2 collisionBubble(const int bubbleRadius, const glm::vec2 bubblePosition) const;

private:

	bool loadLevel(const string& levelFile);//, const string& tilesetFile = "images/pangTileset.json");
	void prepareArrays(const glm::vec2& minCoords, ShaderProgram& program);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	int nTiles;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	Texture tilesheet;
	glm::vec2 tileTexSize;

	int* interactive;
	int* foreground;
	int* stairs;

	bool* colisions;
	bool* stairsmap;

};


#endif // _TILE_MAP_INCLUDE


