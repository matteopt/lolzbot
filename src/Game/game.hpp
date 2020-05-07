#pragma once
#include <Windows.h>
#include <cstdio>
#include "../Utils/find_hwnd.hpp"
#include "../Utils/processing.hpp"

namespace Game {
	extern HWND hwnd;
	extern RECT rect;
	extern HDC hdc;

	void Init();

	void Play();
	bool IsReady();
}