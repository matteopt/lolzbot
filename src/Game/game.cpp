#include "game.hpp"

HWND Game::hwnd;
RECT Game::rect;
Processing::HDC_t Game::gdc;

Game::Side Game::side;
Game::Role Game::role;

void Game::Init() {
	printf("Looking for game window...\n");

	// get the window handle and rectangle info for the game window
	hwnd = NULL;
	while (hwnd == NULL) {
		hwnd = Utils::FindHwnd("League of Legends (TM) Client");
		if (hwnd)
			GetWindowRect(hwnd, &rect);

		Sleep(2000);
	}
	printf("Game window found!\n");

	Sleep(1000);

	// get the devide context for the window
	gdc = Processing::HDC_t(GetDC(hwnd), 1280, 720);

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

	while (Processing::CompareRGB(GetPixel(gdc.hdc, 0, 0), 0, 0, 0))
		Sleep(100);
	
	Sleep(500);

	side = GetSide();
	role = Game::Role::TOP;

	// lock camera
	Input::Key(VK_SPACE);

	while (true) {
		int turret_x, turret_y;
		Side turret_side;
		if (Processing::FindTurret(Processing::Screenshot(gdc), turret_x, turret_y, turret_side)) {
			if (side != turret_side)
				printf("CLOSE TO ENEMY TURRET!!!\n");
		}
		Sleep(1000);
	}

	// release/delete context-related stuff
	ReleaseDC(hwnd, gdc.hdc);
	DeleteObject(gdc.hdc);
	DeleteObject(gdc.hcdc);
	DeleteObject(gdc.hbmp);
}

bool Game::IsReady() {
	COLORREF color = GetPixel(gdc.hdc, 630, 715);
	return !Processing::CompareRGB(color, 0, 11, 19);
}

Game::Side Game::GetSide() {
	cv::Mat img = Processing::Screenshot(gdc);
	double p = Processing::MatchTemplate(img, "bside.png");
	printf("%.2f\n", p);
	if (p > 0.5f)
		return Game::Side::BLUE;
	else
		return Game::Side::RED;
}

void Game::Click(const int rel_x, const int rel_y, const bool right_click) {
	Input::Click(rect.left + rel_x, rect.top + 25 + rel_y, right_click);
}

void Game::MinimapClick(const int rel_x, const int rel_y, const bool right_click) {
	Click(1099 + rel_x, 539 + rel_y, right_click);
}
