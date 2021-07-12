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

#ifndef __YARE_SDLTEXTURE_H
#define __YARE_SDLTEXTURE_H

#include "texture.h"
#include "renderer.h"
#include "definitions.h"

#include <SDL2/SDL.h>

class SdlFont;

class SdlTexture : public Texture {
public:
	friend class SdlFont;

public:
	SdlTexture();

	void release() override;
	bool loadFromFile(const std::string& filename) override;
	void draw(Renderer &renderer, Rect destination, Rect source) override;
	void draw(Renderer &renderer, Rect destination) override;

private:
	SDL_Surface *surface;
	SDL_Texture *texture;
};


#endif // __YARE_SDLTEXTURE_H
