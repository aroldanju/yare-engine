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

#ifndef __YARE_MAP_H
#define __YARE_MAP_H

#include <cstdint>
#include <fstream>
#include "renderer.h"
#include "rect.h"
#include "player.h"

class Map
{
public:
	Map();
	Map(uint32_t width, uint32_t height);
	virtual ~Map();

	uint32_t getWidth() const;

	uint32_t getHeight() const;

	bool checkCollision(uint32_t x, uint32_t y) const ;

	void setTile(uint32_t x, uint32_t y, uint16_t tile);

	void setTiles(const uint16_t *tiles);

	uint16_t getTile(uint32_t x, uint32_t y) const;

	bool loadFromFile(const std::string& filename);

	void draw(Renderer& renderer, const Player &player);

private:
	uint32_t width, height;
	uint16_t *tiles;
};

#endif // __YARE_MAP_H
