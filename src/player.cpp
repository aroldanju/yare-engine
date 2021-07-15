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
#include <iostream>
#include "player.h"
#include "definitions.h"
#include "map.h"

Player::Player() :
	position((Position){ 0.0f, 0.0f }),
	tilePosition((Position){ 0.0f, 0.0f }),
	angle(0.0f * (M_PI / 180.0f)),
	moving(0.0f),
	rotating(0.0f),
	velocityMove(8.0f),
	velocityRotate(3.0f * (M_PI / 180.0f)),
	fov(60.0f * (M_PI / 180.0f))
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

	// Last raycast
	if (!this->lastRaycast.empty()) {
		renderer.setColor(128, 128, 128, 64);
		for (auto& ray : this->lastRaycast) {
			renderer.drawLine(this->position.x, this->position.y, ray.position.x, ray.position.y);
		}
	}
}

float Player::getFov() const {
	return this->fov;
}

void Player::raycast(const Map &map) {

    const uint32_t rays = SCREEN_WIDTH;

	const float fovVariation = this->fov / rays;

	//auto start = std::chrono::steady_clock::now();

	lastRaycast.clear();
	for (uint32_t i = 0; i < rays; i++) {
		lastRaycast.push_back(singleRaycast(map, fovVariation * i));
	}

	//const uint32_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
	//std::cout << "Elapsed: " << elapsed << "ms" << std::endl;
}

Ray Player::singleRaycast(const Map &map, float variation) {

	// TODO use triangles to improve performance

	const uint32_t iterations = 4096;
	const float fovMiddle = this->fov / 2.0f;
	const float rayAngle = this->angle - fovMiddle + variation;

	for (int i = 0; i < iterations; i++) {
		float x = this->position.x + std::cos(rayAngle) * (float)i;
		float y = this->position.y + std::sin(rayAngle) * (float)i;

		if (map.checkCollision(x / TILE_SIZE, y / TILE_SIZE)) {
			bool collideX = (int)std::floor(x) % TILE_SIZE != 0;
			// Ray to left?
			if (collideX && rayAngle > M_PI / 2.0f && rayAngle < 3.0 * M_PI / 2.0) {
                x += 1.0f;
                collideX = (int)std::floor(x) % TILE_SIZE != 0;
			}

			return (Ray){ (Position){x, y},
				 rayAngle,
				 collideX
			};
		}
	}

	return (Ray){ (Position){-1.0f, -1.0f}, 0.0f };
}


const std::vector<Ray>& Player::getLastRaycast() const {
	return this->lastRaycast;
}
