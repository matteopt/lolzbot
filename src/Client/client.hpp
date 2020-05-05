#pragma once

#define LEAGUECLIENT_PATH L"C:\\Games\\Riot Games\\League of Legends\\LeagueClient.exe"

namespace Client {

	HWND hwnd;
	RECT rect;

	void Launch() {
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		CreateProcess(LEAGUECLIENT_PATH, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}

	void Init() {
		printf("Starting LeagueClient.exe...\n");
		Launch();

		hwnd = NULL;
		while (hwnd == NULL || rect.right - rect.left != 1280) {
			hwnd = Utils::FindHwnd("League of Legends");
			if (hwnd)
				GetWindowRect(hwnd, &rect);

			Sleep(500);
		}
		printf("Client window found!\n");

		SetForegroundWindow(hwnd);
		SetActiveWindow(hwnd);
		SetFocus(hwnd);
	}

	void Click(int rel_x, int rel_y, bool right_click) {
		Input::Click(rect.right + rel_x, rect.top + rel_y, right_click);
	}
}
