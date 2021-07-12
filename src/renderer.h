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

#ifndef __YARE_RENDERER_H
#define __YARE_RENDERER_H

#include <cstdint>
#include <string>

class Renderer {
public:
    virtual ~Renderer() = default;

    virtual void clear(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) = 0;
    virtual void render() = 0;

    virtual bool initialize(const std::string& title, uint32_t width, uint32_t height) = 0;
    virtual void release() = 0;

    virtual void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) = 0;
    virtual void drawLine(int x0, int y0, int x1, int y1) = 0;
    virtual void drawRect(int x, int y, int w, int h) = 0;

};

#endif // __YARE_RENDERER_H
