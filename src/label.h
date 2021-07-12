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

#ifndef __YARE_LABEL_H
#define __YARE_LABEL_H

#include "color.h"
#include "texture.h"
#include "font.h"

#include <memory>
#include <string>

class Label {
public:
	Label(Font &font);
	virtual ~Label();

	void setCaption(const std::string& caption);
	void setColor(const Color &color);
	void release();

	void draw(Renderer& renderer, const Position &position);

private:
	Font& font;
	std::unique_ptr<Texture> texture;
	Color color;
	std::string caption;
};


#endif // __YARE_LABEL_H
