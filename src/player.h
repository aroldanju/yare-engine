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

#ifndef __YARE_PLAYER_H
#define __YARE_PLAYER_H

#include <vector>

#include "rect.h"
#include "map.h"

class Player {
public:
	Player();
	virtual ~Player() = default;

	void setPosition(const Position &position);

	void ahead();
	void back();
	void left();
	void right();
	void stopMoving();
	void stopRotating();

	void update(const Map &map);

	const Position& getPosition() const;

	float getAngle() const;

	void draw(Renderer& renderer);

	void raycast(const Map &map);
	Ray singleRaycast(const Map &map, float );

	const std::vector<Ray>& getLastRaycast() const;

private:
	Position position;
	Position tilePosition;
	float angle;
	float moving, rotating;
	float velocityMove, velocityRotate;
	float fov;
	std::vector<Ray> lastRaycast;

};


#endif // __YARE_PLAYER_H
