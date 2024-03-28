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

glm::ivec4 TileMap::checkStairs(glm::ivec2& posi, const glm::ivec2& size, const glm::ivec2& sizeoff)
{
	int x, y, y1, x1;

	x = (posi.x + sizeoff.x) / tileSize;
	x1 = (posi.x + sizeoff.x + size.x - 1) / tileSize;

	y = (posi.y + sizeoff.y) / tileSize;
	y1 = (posi.y + sizeoff.y + size.y) / tileSize;

	glm::ivec4 stair = glm::ivec4(-1, -1, -1, -1);

	for (int _y = y1; _y >= y; _y--)
	{
		for (int _x = x; _x <= x1; _x++)
		{
			if (stairsmap[_y * mapSize.x + _x])
			{
				//Busco la primera escala, la 16
				int i = 0;
				if (stairs[_y * mapSize.x + _x] == 17)
					i = -1;
				else if (stairs[_y * mapSize.x + _x] == 18)
					i = -2;
				if (stairs[_y * mapSize.x + _x + i] == 16)
					stair.x = (_x + i) * tileSize -tileSize/2;

				//Ara busco la part superior de l'escala
				int j = 0;
				while (stairsmap[(_y - j) * mapSize.x + x])
					j++;
				stair.y = (_y - (j-1)) * tileSize;
				//I ara la part inferior
				j = 0;
				while (stairsmap[(_y + j) * mapSize.x + x])
					j++;
				stair.z = (_y + (j-1)) * tileSize;

				stair.w = stair.x + 3 * tileSize;
				_y = y;
			}
		}
	}
	return stair;
}

bool TileMap::checkStairsBelow(glm::ivec2& posi, const glm::ivec2& size, const glm::ivec2& sizeoff)
{
	int x, y, y1, x1;

	x = (posi.x + sizeoff.x) / tileSize;
	y = (posi.y + sizeoff.y ) / tileSize +2;
	x1 = (posi.x + sizeoff.x + size.x) / tileSize;

	y1 = (posi.y + sizeoff.y + size.y ) / tileSize;

	for (int _x = x; _x <= x1; _x++)
	{
		for (int _y = y; _y <= y1; _y++)
		{
			if (stairsmap[_y * mapSize.x + _x])
			{
				return true;
			}
		}
	}
	return false;
}

bool TileMap::groundWithStairsBelow(glm::ivec2& posi, const glm::ivec2& size, const glm::ivec2& sizeoff)
{
	int x, y1, x1;

	x = (posi.x + sizeoff.x) / tileSize;
	x1 = (posi.x + sizeoff.x + size.x) / tileSize;

	y1 = (posi.y + sizeoff.y + size.y) / tileSize;

	for (int _x = x; _x <= x1; _x++)
	{
		if (stairsmap[y1 * mapSize.x + _x])
		{
			return true;
		}
	}
	return false;
}

short TileMap::collisionMove(glm::ivec2* pos, const glm::ivec2& size, const glm::ivec2& sizeoff, const glm::ivec2 dir) const
{
	if (dir.x != 0 || dir.y != 0)
	{
		int x, y, y1, x1;
		glm::ivec2 posi = *pos;
		short col = 0b0000;

		//Nova posicio de la capsa en tilespace
		x =  (posi.x + sizeoff.x + dir.x ) / tileSize;
		x1 = (posi.x + sizeoff.x + size.x + dir.x) / tileSize;

		y =  (posi.y + sizeoff.y + dir.y) / tileSize;
		y1 = (posi.y + sizeoff.y + size.y + dir.y) / tileSize;

		for (int _y = y; _y <= y1; _y++)
		{
			for (int _x = x; _x <= x1; _x++)
			{
				cout << "(" << _x << "," << _y << ")" << stairs[_y * mapSize.x + _x] << " ";
			}
			cout << endl;
		}
		cout << endl;

		if (dir.x > 0)
		{
			for (int _y = y; !(col&0b1000) && _y <= y1-1; _y++)
			{
				if (colisions[_y * mapSize.x + x1])
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
				if (colisions[_y * mapSize.x + x])
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
				if (colisions[y1 * mapSize.x + _x])
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

glm::ivec2 TileMap::collisionBubble(const int bubbleRadius, const glm::vec2 bubblePosition) const
{
	int bubbleGridX = bubblePosition.x / tileSize;
	int bubbleGridY = bubblePosition.y / tileSize;

	int bubbleRadiusSquared = bubbleRadius * bubbleRadius;

	for (int yOffset = -1; yOffset <= 1; ++yOffset) {
		for (int xOffset = -1; xOffset <= 1; ++xOffset) {
			int checkX = bubbleGridX + xOffset;
			int checkY = bubbleGridY + yOffset;

			if (colisions[checkY * mapSize.x + checkX] && checkX >= 0 && checkX < mapSize.x && checkY >= 0 && checkY < mapSize.y) {
				int cellCenterX = (checkX + 0.5) * tileSize;
				int cellCenterY = (checkY + 0.5) * tileSize;

				int dx = cellCenterX - bubblePosition.x;
				int dy = cellCenterY - bubblePosition.y;
				int distanceSquared = dx * dx + dy * dy;

				if (distanceSquared <= bubbleRadiusSquared) {

					if (std::abs(dx) > std::abs(dy)) {
						return glm::ivec2(dx > 0 ? 1 : -1, 0);
					}
					else if(std::abs(dx) < std::abs(dy)) {
						return glm::ivec2(0, dy > 0 ? 1 : -1);
					}
					else
						return glm::ivec2(dx > 0 ? 1 : -1, dy > 0 ? 1 : -1);
				}
			}
		}
	}
	return glm::ivec2(0,0);
}






























