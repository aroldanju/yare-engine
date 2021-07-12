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

#include <iostream>
#include "sdlfont.h"
#include "sdltexture.h"

SdlFont::SdlFont() :
	font(nullptr)
{

}

void SdlFont::release() {
	if (this->font) {
		TTF_CloseFont(this->font);
	}

	this->font = nullptr;
}

bool SdlFont::loadFromFile(const std::string& filename, uint32_t size) {
	this->font = TTF_OpenFont(filename.c_str(), size);

	return this->font != nullptr;
}

std::unique_ptr<Texture> SdlFont::render(const std::string& text, const Color &color) {
	std::unique_ptr<Texture> texture = std::unique_ptr<Texture>(new SdlTexture());
	SdlTexture *sdlTexture = reinterpret_cast<SdlTexture*>(texture.get());

	sdlTexture->surface = TTF_RenderText_Blended(this->font, text.c_str(), (SDL_Color){color.r, color.g, color.b, color.a});

	return std::move(texture);
}
