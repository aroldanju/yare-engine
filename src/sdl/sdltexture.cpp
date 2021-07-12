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

#include "sdltexture.h"

#include "sdlrenderer.h"

SdlTexture::SdlTexture() :
	surface(nullptr),
	texture(nullptr)
{
}

void SdlTexture::release() {
	SDL_FreeSurface(this->surface);
	SDL_DestroyTexture(this->texture);
}

bool SdlTexture::loadFromFile(const std::string& filename)	{
	this->surface = SDL_LoadBMP(filename.c_str());
	return (this->surface != nullptr);
}

void SdlTexture::draw(Renderer &renderer, Rect destination, Rect source) {
	SdlRenderer &sdlRenderer = reinterpret_cast<SdlRenderer&>(renderer);
	SDL_Rect src = (SDL_Rect){(int)source.position.x, (int)source.position.y, (int)source.size.width, (int)source.size.height};
	SDL_Rect dst = (SDL_Rect){(int)destination.position.x, (int)destination.position.y, (int)destination.size.width, (int)destination.size.height};

	if (!this->texture) {
		this->texture = SDL_CreateTextureFromSurface(sdlRenderer.renderer, this->surface);
	}

	SDL_RenderCopy(sdlRenderer.renderer, this->texture, &src, &dst);
}

void SdlTexture::draw(Renderer &renderer, Rect destination) {
	SdlRenderer &sdlRenderer = reinterpret_cast<SdlRenderer&>(renderer);
	int w = destination.size.width == 0.0f ? surface->w : destination.size.width;
	int h = destination.size.height == 0.0f ? surface->h : destination.size.height;
	SDL_Rect src = (SDL_Rect){0, 0, 0, 0};
	SDL_Rect dst = (SDL_Rect){(int)destination.position.x, (int)destination.position.y, (int)w, (int)h};

	if (!this->texture) {
		this->texture = SDL_CreateTextureFromSurface(sdlRenderer.renderer, this->surface);
	}

	SDL_RenderCopy(sdlRenderer.renderer, this->texture, nullptr, &dst);
}
