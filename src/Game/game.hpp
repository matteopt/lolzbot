#pragma once
#include <Windows.h>
#include <cstdio>
#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>
#include "../Utils/find_hwnd.hpp"
#include "../Utils/processing.hpp"
#include "../Utils/input.hpp"
#include "shop.hpp"

namespace Game {

	enum class Side : bool {
		BLUE,
		RED
	};

	enum class Role : unsigned char {
		TOP,
		MID,
		JUNGLE,
		ADC,
		SUPPORT
	};

	extern HWND hwnd;
	extern RECT rect;
	extern Processing::HDC_t gdc;

	extern Side side;
	extern Role role;

	void Init();

	void Play();
	bool IsReady();
	Side GetSide();

	void Click(const int rel_x, const int rel_y, const bool right_click);
	void MinimapClick(const int rel_x, const int rel_y, const bool right_click);
}