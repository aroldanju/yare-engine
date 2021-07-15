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

#ifndef __YARE_SCENE_H
#define __YARE_SCENE_H

#include "map.h"
#include "player.h"
#include "assetmanager.h"

class Scene {
public:
	Scene(Size viewport, Map &map, Player &player);
	virtual ~Scene() = default;

	void draw(Renderer &renderer, AssetManager &assetManager);

private:
	Map &map;
	Player &player;
	Size viewport;
};

#endif // __YARE_SCENE_H
