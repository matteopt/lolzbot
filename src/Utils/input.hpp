#pragma once
#include <Windows.h>
#include "common.hpp"

namespace Input {
	void Click(const int abs_x, const int abs_y, const bool right_click);
	void Keys(const unsigned char n, const uint8_t* const keys);
	void Key(const uint8_t key);
}
