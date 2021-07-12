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

#ifndef __YARE_ASSETMANAGER_H
#define __YARE_ASSETMANAGER_H

#include "texture.h"
#include "font.h"
#include <memory>
#include <map>
#include <string>
#include <cstdint>

class AssetManager {
public:
	AssetManager();
	virtual ~AssetManager() = default;

	void release();

	//bool loadTexture(uint32_t id, const std::string& filename);
	bool addTexture(uint32_t id, std::unique_ptr<Texture>& texture);
	Texture& getTexture(uint32_t id);

	bool addFont(uint32_t id, std::unique_ptr<Font>& font);
	Font& getFont(uint32_t id);

private:
	std::map<uint32_t, std::unique_ptr<Texture>> textures;
	std::map<uint32_t, std::unique_ptr<Font>> fonts;
};


#endif // __YARE_ASSETMANAGER_H
