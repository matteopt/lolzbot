#pragma once
#include "client.hpp"

HWND Client::hwnd;
RECT Client::rect;
HDC Client::hdc;

void Client::Launch() {
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));

	// start LeagueClient.exe
	CreateProcess(LEAGUECLIENT_PATH, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

void Client::Init() {
	printf("Starting LeagueClient.exe...\n");
	Launch();

	// get the window handle and rectangle info for the client window
	hwnd = NULL;
	while (hwnd == NULL || rect.right - rect.left != 1280) {
		hwnd = Utils::FindHwnd("League of Legends");
		if (hwnd)
			GetWindowRect(hwnd, &rect);

		Sleep(500);
	}
	printf("Client window found!\n");

	// get the devide context for the window
	hdc = GetDC(hwnd);

	// just in case the window is in the background
	SetForegroundWindow(hwnd);
	SetActiveWindow(hwnd);
	SetFocus(hwnd);

	// start a game
	Play();
}

void Client::Play() {
	printf("Waiting for client...\n");
	while (!IsReady())
		Sleep(500);

	printf("Client is ready!\n");

	// todo: create a game queue or w/e

	// debug
	Game::Init();
}

bool Client::IsReady() {
	// using the notification icon's color to know when the client has loaded
	COLORREF color = GetPixel(hdc, 1258, 58);
	return Processing::CompareRGB(color, 92, 91, 87);
}

void Client::Click(int rel_x, int rel_y, bool right_click) {
	Input::Click(rect.left + rel_x, rect.top + rel_y, right_click);
}
