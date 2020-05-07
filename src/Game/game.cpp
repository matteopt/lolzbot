#include "game.hpp"

HWND Game::hwnd;
RECT Game::rect;
HDC Game::hdc;

void Game::Init() {
	printf("Looking for game window...\n");

	// get the window handle and rectangle info for the game window
	hwnd = NULL;
	while (hwnd == NULL) {
		hwnd = Utils::FindHwnd("League of Legends (TM) Client");
		if (hwnd)
			GetWindowRect(hwnd, &rect);

		Sleep(500);
	}
	printf("Game window found!\n");

	// get the devide context for the window
	hdc = GetDC(hwnd);

	// just in case the window is in the background
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);
	SetFocus(hwnd);

	Play();
}

void Game::Play() {
	printf("Waiting for game...\n");
	Sleep(5000);

	while (!IsReady())
		Sleep(500);

	printf("Game is ready!\n");

	while (Processing::CompareRGB(GetPixel(hdc, 0, 0), 0, 0, 0))
		Sleep(100);
}

bool Game::IsReady() {
	COLORREF color = GetPixel(hdc, 630, 715);
	return !Processing::CompareRGB(color, 0, 11, 19);
}

void Game::Click(int rel_x, int rel_y, bool right_click) {
	Input::Click(rect.right + rel_x, rect.top + rel_y, right_click);
}
