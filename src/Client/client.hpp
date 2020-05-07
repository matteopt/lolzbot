#pragma once
#include <Windows.h>
#include <cstdio>
#include "../Utils/find_hwnd.hpp"
#include "../Utils/processing.hpp"
#include "../Utils/input.hpp"

#define LEAGUECLIENT_PATH L"C:\\Games\\Riot Games\\League of Legends\\LeagueClient.exe"

namespace Client {
	extern HWND hwnd;
	extern RECT rect;
	extern HDC hdc;

	void Launch();
	void Init();

	void Play();
	bool IsReady();

	void Click(int rel_x, int rel_y, bool right_click);
}
