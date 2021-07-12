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

#ifndef __YARE_FONT_H
#define __YARE_FONT_H

#include "color.h"
#include "texture.h"
#include <string>
#include <memory>

class Font {
public:
	virtual void release() = 0;
	virtual bool loadFromFile(const std::string &filename, uint32_t size) = 0;
	virtual std::unique_ptr<Texture> render(const std::string& text, const Color &color) = 0;
};

#endif // __YARE_FONT_H
