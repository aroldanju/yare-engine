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

#include "label.h"

Label::Label(Font &font) :
	font(font),
	texture(nullptr),
	color((Color){0, 0, 0}),
	caption("Label")
{
}

Label::~Label() {

}

void Label::setColor(const Color &color) {
	this->color = color;

	this->texture = this->font.render(this->caption, this->color);
}

void Label::setCaption(const std::string &caption) {
	this->caption = caption;

	this->texture = this->font.render(this->caption, this->color);
}

void Label::release() {
	if (this->texture) {
		this->texture.release();
	}
}

void Label::draw(Renderer& renderer, const Position &position)	{
	if (this->texture) {
		this->texture->draw(renderer, (Rect){position, (Size){0.0f, 0.0f}});
	}
}