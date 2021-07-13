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

#ifndef __YARE_EVENTHANDLER_H
#define __YARE_EVENTHANDLER_H

#include <functional>

class EventHandler {
public:
	enum Key_t {
		KEY_LEFT,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_TAB
	};

public:
	virtual void handle() = 0;

	void setOnKeyUpListener(const std::function<void(Key_t)>& listener) {
		this->onKeyUpListener = listener;
	}

	void setOnKeyDownListener(const std::function<void(Key_t)>& listener) {
		this->onKeyDownListener = listener;
	}

	void setOnQuitListener(const std::function<void()>& listener) {
		this->onQuitListener = listener;
	}

protected:
	void onKeyUp(Key_t key)	{
		if (this->onKeyUpListener) {
			this->onKeyUpListener(key);
		}
	}

	void onKeyDown(Key_t key)	{
		if (this->onKeyDownListener) {
			this->onKeyDownListener(key);
		}
	}

	std::function<void(Key_t)> onKeyUpListener;
	std::function<void(Key_t)> onKeyDownListener;
	std::function<void()> onQuitListener;
};

#endif //__YARE_EVENTHANDLER_H
