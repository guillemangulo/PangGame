#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"




using namespace std;


TileMap* TileMap::createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program)
{
	TileMap* map = new TileMap(levelFile, minCoords, program);

	return map;
}


TileMap::TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
}

TileMap::~TileMap()
{
	free();
	if (stairs != NULL)
		delete stairs;
	if (foreground != NULL)
		delete foreground;
	if (interactive != NULL)
		delete interactive;
	if(colisions != NULL)
		delete colisions;
	if (stairsmap != NULL)
		delete stairsmap;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * nTiles);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}


bool TileMap::loadLevel(const string& levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	char tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	int size = mapSize.x * mapSize.y;
	interactive = new int[size];
	foreground = new int[size];
	stairs = new int[size];

	colisions = new bool[size];
	stairsmap = new bool[size];

	getline(fin, line);
	if (line.compare(0, 4, "CAPA") != 0)
	{
		getline(fin, line);
	}
	else {
		for (int i = 0; i < size; ++i) {
			std::string token;
			if (i == size - 1)
				std::getline(fin, token);
			else
				std::getline(fin, token, ',');
			foreground[i] = std::stoi(token);
		}
	}
	getline(fin, line);
	if (line.compare(0, 4, "CAPA") != 0)
	{
		getline(fin, line);
	}
	else {
		for (int i = 0; i < size; ++i) {
			std::string token;
			if (i == size - 1)
				std::getline(fin, token);
			else
				std::getline(fin, token, ',');

			interactive[i] = std::stoi(token);
			if (interactive[i] != 0)
				colisions[i] = true;
			else
				colisions[i] = false;
		}
	}
	getline(fin, line);
	if (line.compare(0, 4, "CAPA") != 0)
	{
		getline(fin, line);
	}
	else {
		for (int i = 0; i < size; ++i) {
			std::string token;
			if (i == size - 1)
				std::getline(fin, token);
			else
				std::getline(fin, token, ',');

			stairs[i] = std::stoi(token);
			if (stairs[i] != 0)
				stairsmap[i] = true;
			else
				stairsmap[i] = false;
		}
	}

	return true;
}//*/


void TileMap::prepareArrays(const glm::vec2& minCoords, ShaderProgram& program)
{
	int tile;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	nTiles = 0;
	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			tile = interactive[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile - 1) % tilesheetSize.x) / tilesheetSize.x, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
			tile = stairs[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile - 1) % tilesheetSize.x) / tilesheetSize.x, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
			tile = foreground[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile - 1) % tilesheetSize.x) / tilesheetSize.x, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.


short TileMap::collisionMove(glm::ivec2* pos, const glm::ivec2& size, const glm::ivec2& sizeoff, const glm::ivec2 dir) const
{
	if (dir.x != 0 || dir.y != 0)
	{
		int x, y, y1, x1;
		glm::ivec2 posi = *pos;
		short col = 0b0000;

		//Nova posicio de la capsa en tilespace
		x =  (posi.x + sizeoff.y + dir.x -1) / tileSize;
		x1 = (posi.x + sizeoff.x + size.x + dir.x) / tileSize;

		y =  (posi.y + sizeoff.x + dir.y-1) / tileSize;
		y1 = (posi.y + sizeoff.y + size.y + dir.y) / tileSize;

		for (int _y = y; _y <= y1; _y++)
		{
			for (int _x = x; _x <= x1; _x++)
			{
				cout << "(" << _x << "," << _y << ")" << colisions[_y * mapSize.x + _x] << " ";
			}
			cout << endl;
		}
		cout << endl;

		if (dir.x > 0)
		{
			for (int _y = y; !(col&0b1000) && _y <= y1-1; _y++)
			{
				if (colisions[_y * mapSize.x + x1] != 0)
				{
					col |= 0b1000;
					//TODO: aplicar correccio de colisio per que quedi just a la vora del bloc?
				}

			}
			if (!(col & 0b1000))
			{
				pos->x += dir.x;
			}

		}
		else if (dir.x < 0)
		{
			for (int _y = y; !(col & 0b0100) && _y <= y1-1; _y++)
			{
				if (colisions[_y * mapSize.x + x] != 0)
				{
					col |= 0b0100;
					//TODO: aplicar correccio de colisio per que quedi just a la vora del bloc?
				}
			}
			if (!(col & 0b0100))
			{
				pos->x += dir.x;
			}
		}
		if (dir.y > 0)
		{
			for (int _x = x; !(col & 0b0001) && _x <= x1; _x++)
			{
				if (colisions[y1 * mapSize.x + _x] != 0)
				{
					col |= 0b0001;
					pos->y = (y1) * tileSize - size.y;
				}
			}
			if (!(col & 0b0001))
			{
				pos->y += dir.y;
			}
		}
		return col;
	}
	return 0b10000;
}


bool TileMap::advCollisionMoveBox(const glm::ivec2& pos, const glm::ivec2& size, const glm::ivec2& dir) const
{
	return false;
}

bool TileMap::advCollisionMoveSphere(const glm::ivec2& pos, const float radius, const glm::ivec2& dir) const
{
	return false;
}

bool TileMap::isFloorTile(int x, int y) const {
	if (x < 0 || x >= mapSize.x || y < 0 || y >= mapSize.y) return true; // out of bounds
	
	int tileIndex = interactive[y * mapSize.x + x];

}






























