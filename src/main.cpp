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

#include <sdl/sdlfont.h>
#include <sdl/sdlrenderer.h>
#include <sdl/sdleventhandler.h>
#include <sdl/sdltexture.h>
#include <label.h>
#include <assetmanager.h>
#include <map.h>
#include <player.h>
#include <scene.h>

#include <iostream>
#include <chrono>
#include <sstream>

int main(int argc, char *argv[]) {
	SdlRenderer renderer;
	SdlEventHandler eventHandler;
	AssetManager assetManager;
	Player player;

	bool showMap = false;
	bool quit = false;
	uint32_t fps = 0;
	auto timeStart = std::chrono::steady_clock::now();

	Map map;
	map.loadFromFile("../../assets/map.map");

	Scene scene((Size){SCREEN_WIDTH, SCREEN_HEIGHT}, map, player);

	player.setPosition((Position){TILE_SIZE + TILE_SIZE / 2, TILE_SIZE + TILE_SIZE /2});

	renderer.initialize("Yare", SCREEN_WIDTH, SCREEN_HEIGHT);

	std::unique_ptr<Font> font = std::unique_ptr<Font>(new SdlFont());
	font->loadFromFile("../../assets/PIXEARG_.TTF", 8);
	assetManager.addFont(0, font);

	std::unique_ptr<Texture> texture = std::unique_ptr<Texture>(new SdlTexture());
	texture->loadFromFile("../../assets/bricks.bmp");
	assetManager.addTexture(0, texture);

	Label labelFps(assetManager.getFont(0));
	labelFps.setCaption("FPS 60");
	labelFps.setColor((Color){255, 255, 0});

	eventHandler.setOnQuitListener([&]() -> void {
		quit = true;
	});

	eventHandler.setOnKeyDownListener([&](EventHandler::Key_t key) -> void {
		switch (key) {
			case EventHandler::KEY_RIGHT: player.right(); break;
			case EventHandler::KEY_LEFT: player.left(); break;
			case EventHandler::KEY_UP: player.ahead(); break;
			case EventHandler::KEY_DOWN: player.back(); break;
			case EventHandler::KEY_TAB: showMap = !showMap; break;
		}
	});

	eventHandler.setOnKeyUpListener([&](EventHandler::Key_t key) -> void {
		switch (key) {
			case EventHandler::KEY_RIGHT: player.stopRotating(); break;
			case EventHandler::KEY_LEFT: player.stopRotating(); break;
			case EventHandler::KEY_UP: player.stopMoving(); break;
			case EventHandler::KEY_DOWN: player.stopMoving(); break;
		}
	});

	timeStart = std::chrono::steady_clock::now();

	while (!quit) {
		auto timeFrameStart = std::chrono::steady_clock::now();

		eventHandler.handle();

		renderer.clear();

		scene.draw(renderer, assetManager);

		if(showMap) {
			map.draw(renderer, player);
		}

		labelFps.draw(renderer, (Position) {0, 0});
		renderer.render();

		player.update(map);
		player.raycast(map);

		SDL_Delay(1);
		uint32_t elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeFrameStart).count();
		if (elapsed < FPS_DELAY) {
			SDL_Delay(FPS_DELAY - elapsed);
		}

		fps++;
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - timeStart).count() >= 1000) {
			std::stringstream ss;
			ss << "FPS " << fps;
			labelFps.setCaption(ss.str());
			timeStart = std::chrono::steady_clock::now();
			fps = 0;
		}
	}

	labelFps.release();
	font.release();
	renderer.release();

	return 0;
}
