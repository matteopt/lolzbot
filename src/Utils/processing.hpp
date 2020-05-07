#pragma once
#include <Windows.h>
#include <cstdint>

namespace Processing {
	void GetRGB(const COLORREF color, uint8_t& r, uint8_t& g, uint8_t& b);
	bool CompareRGB(const COLORREF color, const uint8_t r, const uint8_t g, const uint8_t b);
}
