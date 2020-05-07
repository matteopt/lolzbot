#pragma once
#include <random>

namespace Common {
	extern int screen_x;
	extern int screen_y;

	extern std::random_device rngdev;
	extern std::mt19937 rng;
	extern std::uniform_int_distribution<std::mt19937::result_type> dmstime;
}
