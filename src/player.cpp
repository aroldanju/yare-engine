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

#include <cmath>
#include "player.h"
#include "definitions.h"

Player::Player() :
	position((Position){ 0.0f, 0.0f }),
	tilePosition((Position){ 0.0f, 0.0f }),
	angle(0.0f),
	moving(0.0f),
	rotating(0.0f),
	velocityMove(8.0f),
	velocityRotate(3.0f * (M_PI / 180.0f))
{

}

void Player::setPosition(const Position &position)	{
	this->position = position;
}

const Position& Player::getPosition() const {
	return this->position;
}

float Player::getAngle() const {
	return this->angle;
}

void Player::ahead() {
	this->moving = 1.0f;
}

void Player::back() {
	this->moving = -1.0f;
}

void Player::left() {
	this->rotating = -1.0f;
}

void Player::right() {
	this->rotating = 1.0f;
}

void Player::stopMoving()   {
	this->moving = 0.0f;
}

void Player::stopRotating() {
	this->rotating = 0.0f;
}

void Player::update(const Map &map)   {
	Position lastPosition = this->position;

	this->position.x += this->moving * (std::cos(this->angle) * velocityMove);
	this->position.y += this->moving * (std::sin(this->angle) * velocityMove);

	this->angle += this->rotating * velocityRotate;
	if (this->angle < 0.0f) {
		this->angle = (M_PI * 2.0) + this->angle;
	}
	else if (this->angle > M_PI * 2.0) {
		this->angle = this->angle - (M_PI * 2.0);
	}

	if (map.checkCollision(this->position.x / TILE_SIZE, this->position.y / TILE_SIZE)) {
		this->position = lastPosition;
	}

	// Update tile position
	this->tilePosition = (Position){this->position.x / TILE_SIZE, this->position.y / TILE_SIZE};
}

void Player::draw(Renderer& renderer)	{
	// Direction
	renderer.setColor(128, 128, 128);
	renderer.drawLine(this->position.x, this->position.y, this->position.x + std::cos(this->angle) * 20.0f, this->position.y + std::sin(this->angle) * 20.0f);

	// Triangle (x, y)
	renderer.setColor(0, 128, 0);
	renderer.drawLine(this->position.x, this->position.y, this->position.x + std::cos(this->angle) * 20.0f, this->position.y);
	renderer.setColor(0, 0, 128);
	renderer.drawLine(this->position.x, this->position.y, this->position.x, this->position.y + std::sin(this->angle) * 20.0f);

	// Player
	renderer.setColor(0, 255, 0);
	renderer.drawRect((int)(this->position.x - 4.0f), (int)(this->position.y - 4.0f), 8, 8);
}
