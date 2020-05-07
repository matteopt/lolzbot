#pragma once
#include <Windows.h>

namespace Utils {

	struct FindHwnd_t {
		HWND hwnd;
		const char* title;
	};

	BOOL CALLBACK EnumWindowCallback(HWND hwnd, LPARAM lparam);
	HWND FindHwnd(const char* title);
}
