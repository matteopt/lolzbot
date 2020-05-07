#pragma once
#include <Windows.h>
#include <cstdio>
#include "../Utils/find_hwnd.hpp"
#include "../Utils/processing.hpp"
#include "../Utils/input.hpp"
#include "shop.hpp"

namespace Game {
	extern HWND hwnd;
	extern RECT rect;
	extern HDC hdc;

	void Init();

	void Play();
	bool IsReady();

	void Click(int rel_x, int rel_y, bool right_click);
}