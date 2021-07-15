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

#include "scene.h"
#include "definitions.h"
#include <cmath>
#include <iostream>

Scene::Scene(Size viewport, Map &map, Player &player) :
	map(map),
	player(player),
	viewport(viewport)
{
}

void Scene::draw(Renderer &renderer, AssetManager &assetManager) {
	const float maxDistance = std::sqrt(this->viewport.width * this->viewport.width + this->viewport.height * this->viewport.height);
	int i = 0;
	const std::vector<Ray>& raycast = player.getLastRaycast();
	if (raycast.size() == 0) {
		return;
	}

	const float heightMiddle = (float)this->viewport.height / 2.0f;
	const float distanceProjection = ((float)this->viewport.width / 2.0f) / std::tan(player.getFov() / 2.0f);

	// Celling & floor
	renderer.setBlendMode(0);
	renderer.drawGradient(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2, 128, 128, 128, 0, 0, 0);
	renderer.drawGradient(0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2, 0,0,0,64, 64, 64);

	// Set blend mode to apply shadows
	renderer.setBlendMode(1);

	for (auto& ray : raycast) {
		float distance = std::sqrt((ray.position.x - player.getPosition().x) * (ray.position.x - player.getPosition().x) + (ray.position.y - player.getPosition().y) * (ray.position.y - player.getPosition().y));

		// Fix fish-eye
		distance = distance * std::cos(player.getAngle() - ray.angle);

		const float wallHeight = ((float)this->viewport.height/4.0f / distance) * distanceProjection;
		const float y0 = (heightMiddle - (wallHeight / 2.0f));

		float rayTile = 0.0f;
		if (ray.x) {
            rayTile = ray.position.x / (float)TILE_SIZE;
		}
		else {
            rayTile = ray.position.y / (float)TILE_SIZE;
		}
		int floorTile = std::floor(rayTile);
        rayTile = rayTile - floorTile;

		assetManager.getTexture(0).draw(renderer,
                (Rect){(Position){(float)i, y0}, (Size){1.0f, wallHeight}},
                (Rect){(Position){rayTile * (float)TILE_SIZE, 0.0f}, (Size){1.0f, (float)TILE_SIZE}}
        );

        // Apply "deep shadow"
		int color = 180.0f - (180.0f / (maxDistance * 2.0f)) * distance;
        if (ray.x) {
            color += 50;
        }

		if (color < 0) {
			color = 0;
        }

        renderer.setColor(color, color, color, 255);
		renderer.drawLine(i, y0, i, y0 + wallHeight);

		i += (SCREEN_WIDTH / raycast.size());
	}
}
