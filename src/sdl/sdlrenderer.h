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

#ifndef __YARE_SDLRENDERER_H
#define __YARE_SDLRENDERER_H

#include <SDL2/SDL.h>
#include "renderer.h"

class SdlTexture;

class SdlRenderer : public Renderer
{
	friend class SdlTexture;

public:
    SdlRenderer();
    virtual ~SdlRenderer();

    void render() override;
    void clear(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) override;

    bool initialize(const std::string& title, uint32_t width, uint32_t height) override;
    void release() override;

    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) override;
    void drawLine(int x0, int y0, int x1, int y1) override;
    void drawRect(int x, int y, int w, int h) override;

    SDL_Renderer* getRenderer() { return this->renderer; }

    void setBlendMode(int mode) override;

private:
    SDL_Window *window;
    SDL_Renderer *renderer;

};

#endif // __YARE_SDLRENDERER_H
