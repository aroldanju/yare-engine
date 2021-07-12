/*
 *  yare - Yet another raycasting engine
 *  Copyright (C) 2021  A. Roldán
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "map.h"
#include "definitions.h"

#include <cstring>
#include <fstream>
#include <iostream>

Map::Map(uint32_t width, uint32_t height) :
	width(width), height(height),
	tiles(nullptr)
{
	this->tiles = new uint16_t[width * height];
	for (uint32_t i = 0; i < width * height; i++) {
		this->tiles[i] = 0;
	}
}

Map::Map() :
	width(0), height(0),
	tiles(nullptr)
{

}

Map::~Map()
{
	if (this->tiles) {
		delete[] this->tiles;
	}

	this->tiles = nullptr;
}

uint32_t Map::getWidth() const {
	return this->width;
}

uint32_t Map::getHeight() const {
	return this->height;
}

bool Map::checkCollision(uint32_t x, uint32_t y) const {
	return (this->tiles[y * this->width + x] != 0);
}

void Map::setTile(uint32_t x, uint32_t y, uint16_t tile) {
	this->tiles[y * this->width + x] = tile;
}

void Map::setTiles(const uint16_t *tiles)    {
	memcpy(this->tiles, tiles, this->width * this->height * sizeof(uint16_t));
}

uint16_t Map::getTile(uint32_t x, uint32_t y) const  {
	return this->tiles[y * this->width + x];
}

bool Map::loadFromFile(const std::string& filename)	{
	char line[256];
	uint32_t x = 0, y = 0;
	std::ifstream file(filename, std::ifstream::in);
	if (!file.is_open()) {
		return false;
	}

	file.getline(line, 256);
	this->width = std::atoi(line);

	file.getline(line, 256);
	this->height = std::atoi(line);

	this->tiles = new uint16_t[this->width * this->height];
	for (uint32_t i = 0; i < this->width * this->height; i++) {
		this->tiles[i] = 0;
	}

	while (!file.eof()) {
		file.getline(line, 256, ',');
		if (line[0] == '\n') {
			line[0] = line[1];
			line[1] = '\0';
		}

		this->tiles[y * this->width + x] = (uint16_t)std::atoi(line);

		x++;
		if (x >= this->width) {
			y++;
			x= 0;
		}
	}


	file.close();

	/*
	for (int i = 0; i < width * height;i++){
		if (i % width == 0){
			std::cout << std::endl;
		}
		std::cout << tiles[i] << " ";
	}
	*/

	return true;
}

void Map::draw(Renderer& renderer)	{


	// Grid
	renderer.setColor(32, 32, 32);
	for (int i = 0; i < this->width; i++) {
		renderer.drawLine(i * TILE_SIZE, 0, i * TILE_SIZE, this->height * TILE_SIZE);
	}
	for (int i = 0; i < this->height; i++) {
		renderer.drawLine(0, i * TILE_SIZE, this->width * TILE_SIZE, i * TILE_SIZE);
	}


	// Map
	for (int i = 0; i < this->width * this->height; i++) {
		const uint32_t column = i % this->width;
		const uint32_t row = i / this->height;
		const uint32_t tile = this->tiles[row * this->width + column];
		if (tile != 0) {
			renderer.setColor(128, 128, 128);
			renderer.drawRect((int)(column * TILE_SIZE), (int)(row * TILE_SIZE), TILE_SIZE, TILE_SIZE);
		}
	}
}
