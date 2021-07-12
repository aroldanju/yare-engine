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

#include "sdleventhandler.h"

void SdlEventHandler::handle() {
	while (SDL_PollEvent(&this->event)) {
		if (this->event.type == SDL_KEYDOWN) {
			if (this->event.key.keysym.sym == SDLK_LEFT) {
				onKeyDown(KEY_LEFT);
			}
			else if (this->event.key.keysym.sym == SDLK_RIGHT) {
				onKeyDown(KEY_RIGHT);
			}
			else if (this->event.key.keysym.sym == SDLK_UP) {
				onKeyDown(KEY_UP);
			}
			else if (this->event.key.keysym.sym == SDLK_DOWN) {
				onKeyDown(KEY_DOWN);
			}
		}
		else if (this->event.type == SDL_KEYUP) {
			if (this->event.key.keysym.sym == SDLK_LEFT) {
				onKeyUp(KEY_LEFT);
			}
			else if (this->event.key.keysym.sym == SDLK_RIGHT) {
				onKeyUp(KEY_RIGHT);
			}
			else if (this->event.key.keysym.sym == SDLK_UP) {
				onKeyUp(KEY_UP);
			}
			else if (this->event.key.keysym.sym == SDLK_DOWN) {
				onKeyUp(KEY_DOWN);
			}
		}
		else if (this->event.type== SDL_QUIT) {
			if (this->onQuitListener) {
				this->onQuitListener();
			}
		}
	}
}
