#pragma once
#include "find_hwnd.hpp"

BOOL CALLBACK Utils::EnumWindowCallback(HWND hwnd, LPARAM lparam) {
	char title[128];
	GetWindowTextA(hwnd, title, 128);

	// List visible windows with a non-empty title
	if (IsWindowVisible(hwnd)) {
		if (!strcmp(title, reinterpret_cast<FindHwnd_t*>(lparam)->title)) {
			reinterpret_cast<FindHwnd_t*>(lparam)->hwnd = hwnd;
			return FALSE;
		}
	}
	return TRUE;
}

HWND Utils::FindHwnd(const char* title) {
	FindHwnd_t fwnd_t;
	fwnd_t.hwnd = NULL;
	fwnd_t.title = title;

	EnumWindows(EnumWindowCallback, reinterpret_cast<LPARAM>(&fwnd_t));

	return fwnd_t.hwnd;
}
