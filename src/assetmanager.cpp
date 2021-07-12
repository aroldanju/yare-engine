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

#include "assetmanager.h"

AssetManager::AssetManager() {

}

void AssetManager::release() {
	for (auto& texture : this->textures) {
		texture.second->release();
	}
	this->textures.erase(this->textures.begin(), this->textures.end());

	for (auto& font : this->fonts) {
		font.second->release();
	}
	this->fonts.erase(this->fonts.begin(), this->fonts.end());
}

/*
bool AssetManager::loadTexture(const std::string& filename) {
	std::unique_ptr<Texture> texture = std::unique_ptr<Texture>(new SdlTexture());
	if (!texture->loadFromFile(filename)) {
		return false;
	}

	this->textures.insert(std::pair<uint32_t, std::unique_ptr<Texture>(id, std::move(texture)));

	return true;
}
*/

Texture& AssetManager::getTexture(uint32_t index)	{
	auto texture = this->textures.find(index);
	return *texture->second;
}

bool AssetManager::addTexture(uint32_t id, std::unique_ptr<Texture>& texture) {
	this->textures.insert(
			std::pair<uint32_t, std::unique_ptr<Texture>>(id, std::move(texture))
	);

	return true;
}

Font& AssetManager::getFont(uint32_t index)	{
	auto font = this->fonts.find(index);
	return *font->second;
}

bool AssetManager::addFont(uint32_t id, std::unique_ptr<Font>& font) {
	this->fonts.insert(
			std::pair<uint32_t, std::unique_ptr<Font>>(id, std::move(font))
	);

	return true;
}
