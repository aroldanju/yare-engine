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

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_blendmode.h>
#include "sdlrenderer.h"

SdlRenderer::SdlRenderer() :
    window(nullptr),
    renderer(nullptr)
{
}

SdlRenderer::~SdlRenderer()
{
}

void SdlRenderer::render() {
    SDL_RenderPresent(this->renderer);
}

void SdlRenderer::clear(uint8_t r, uint8_t g, uint8_t b) {
    setColor(r, g, b, 255);
    SDL_RenderClear(this->renderer);
}

bool SdlRenderer::initialize(const std::string& title, uint32_t width, uint32_t height)  {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	this->window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width * 2, height * 2, SDL_WINDOW_RESIZABLE);
	if (!this->window) {
		return false;
	}

	this->renderer = SDL_CreateRenderer(this->window, -1, 0);
	if (!this->renderer) {
		return false;
	}

    SDL_RenderSetLogicalSize(this->renderer, width, height);
	SDL_SetRenderDrawBlendMode(this->renderer, SDL_BLENDMODE_ADD);

    return (this->renderer != nullptr && this->window != nullptr);
}

void SdlRenderer::release() {
    if (this->renderer) {
        SDL_DestroyRenderer(this->renderer);
    }
    this->renderer = nullptr;

    if (this->window) {
        SDL_DestroyWindow(this->window);
    }
    this->window = nullptr;

    TTF_Quit();
    SDL_Quit();
}

void SdlRenderer::drawLine(int x0, int y0, int x1, int y1) {
    SDL_RenderDrawLine(this->renderer, x0, y0, x1, y1);
}

void SdlRenderer::drawRect(int x, int y, int w, int h) {
    SDL_Rect rect = (SDL_Rect){ x, y, w, h };
    SDL_RenderFillRect(this->renderer, &rect);
}

void SdlRenderer::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
}

void SdlRenderer::setBlendMode(int mode) {
	SDL_BlendMode sdlBlendMode;
	switch (mode) {
		case 1: sdlBlendMode = SDL_BLENDMODE_MUL; break;
		default:
		case 0: sdlBlendMode = SDL_BLENDMODE_ADD; break;
	}
	SDL_SetRenderDrawBlendMode(this->renderer, sdlBlendMode);
}